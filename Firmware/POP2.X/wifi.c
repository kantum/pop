#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

#include "types.h"
#include "UART.h"
#include "wifi.h"
#include "list.h"
#include "pages.h"
#include "shiftreg.h"

char wifi_response[512];
size_t wifi_async_i = 0;
uint64_t wifi_orders_queue[50];
uint64_t wifi_orders_sz = 0;
size_t	 wifi_op_s_tmsp = 0;

bool wifi_recover(void) {
	int rt = 1;
	while (rt--) {
		if (wifi_init()) { return (true); }
		//delay_ms(1);
	}
	return (false);
}

bool wifi_orders_set(uint64_t id){
	if (wifi_orders_sz < 50) {
		wifi_orders_queue[wifi_orders_sz] = id;
		wifi_orders_sz++;
		return (true);
	} else {
		return (false);
	}
}

uint64_t wifi_orders_get(void){
	size_t i = 1;
	uint64_t ret = wifi_orders_queue[0];
	if (!wifi_orders_sz) return (0x00);
	wifi_orders_sz--;
	while ((i - 1) < wifi_orders_sz && i < 49) {
		wifi_orders_queue[i - 1] = wifi_orders_queue[i];
		i++;
	}
	wifi_orders_queue[i] = 0x00;
	return (ret);
}


void wifi_enable(bool enable) {
	if (!enable)
	{
		wifi_async_status = WIFI_ERROR;
		wifi_curr_op = WIFI_ERROR;
		shiftreg_set(PIN_WIFI_EN, LOW);
	}
	else
	{
		shiftreg_set(PIN_WIFI_EN, HIGH);
		wifi_init();
	}
}

bool wifi_init(void)
{
	size_t rt = 10;
	byte r = 0x00;
	while (rt-- && r != 'O')
	{
		UART_init(115200);
		wifi_flush_uart();
		delay_async_ms(10);
		UART_send_str("!!!S");
		while (!UART_available() && delay_async_status());
		if (UART_available()) UART_read(&r);
		delay_ms(10);
	}
	if (r == 'O') {
		wifi_async_status = WIFI_IDLE;
		wifi_curr_op = WIFI_IDLE;
		wifi_op_s_tmsp = 0;
		return (true);
	} else {
		return (false);
	}
}

bool wifi_disconnect(void)
{
	size_t rt = 10;
	byte r = 0x00;
	while (rt-- && r != 'O')
	{
		wifi_flush_uart();
		delay_async_ms(10);
		UART_send_str("!!!D");
		while (!UART_available() && delay_async_status());
		if (UART_available()) UART_read(&r);
		delay_ms(10);
	}
	if (r == 'O') {
		return (true);
	} else {
		return (false);
	}
}

void wifi_flush_uart(void)
{
	byte tmp;
	while(UART_available()) UART_read(&tmp);
}

bool wifi_connect(char *ssid, char *pass)
{
	UART_send_str("!!!C?");
	UART_send_str(ssid);
	UART_send('~');
	UART_send_str(pass);
	UART_send('~');
	UART_wait_response(1);
	byte r;
	if (!UART_read(&r)) return (false);
	if (r == 'O') return (true);
	return (false);
}

void wifi_load_response(void)
{
	if (wifi_async_status != WIFI_BUSY) return;
	byte rd;
	while (UART_available() && wifi_async_i < 512)
	{
		UART_read(&rd);
		wifi_response[wifi_async_i++] = rd;
		if (wifi_curr_op == WIFI_SCAN) {
			if (rd == '\n' && wifi_response[wifi_async_i - 2] == '\n')
			{ wifi_async_status = WIFI_DONE; return; }
		} else {
			if (rd == '\n') { wifi_async_status = WIFI_DONE; return; }
		}
	}
	if (wifi_async_i == 511) {
		wifi_response[wifi_async_i - 1] = '\n';
		wifi_async_status = WIFI_ERROR; return;
	}
}

bool wifi_async_update(void) {
	if (wifi_async_status == WIFI_ERROR && !wifi_recover()) return (false);
	if (wifi_async_status != WIFI_IDLE) return (false);
	wifi_flush_uart();
	UART_send_str("!!!U");
	wifi_async_status = WIFI_BUSY;
	wifi_async_i = 0;
	wifi_curr_op = WIFI_UPDATE;
	wifi_op_s_tmsp = millis();
	return (true);
}

bool wifi_async_is_ready(void) {
	wifi_load_response();
	return (wifi_async_status == WIFI_DONE);
}

bool wifi_async_check(void) {
	if (wifi_async_is_ready()) {
		UI_request_repaint();
		if (wifi_curr_op == WIFI_UPDATE) {
			wifi_rcv_update();
			uint64_t tmp_id = wifi_orders_get();
			if (tmp_id > 0)
				wifi_async_order(tmp_id);
			return (true); // TODO: HANDLE ERR
		}
		if (wifi_curr_op == WIFI_ORDER) {
			wifi_rcv_order();
			uint64_t tmp_id = wifi_orders_get();
			if (tmp_id > 0)
				wifi_async_order(tmp_id);
			return (true); // TODO: HANDLE ERR
		}
		if (wifi_curr_op == WIFI_SCAN) {
			wifi_rcv_scan();
			uint64_t tmp_id = wifi_orders_get();
			if (tmp_id > 0)
				wifi_async_order(tmp_id);
			return (true); // TODO: HANDLE ERR
		}
	} else {
		if (wifi_async_status == WIFI_BUSY && (
			wifi_curr_op == WIFI_UPDATE ||
			wifi_curr_op == WIFI_ORDER)) {
			if (millis() - wifi_op_s_tmsp > 30000) {
				UI_request_repaint();
				wifi_async_status = WIFI_ERROR;
				return (true);
			}
		} else if (wifi_async_status == WIFI_BUSY &&
				wifi_curr_op == WIFI_SCAN) {
			if (millis() - wifi_op_s_tmsp > 10000) {
				UI_request_repaint();
				wifi_async_status = WIFI_ERROR;
				return (true);
			}
		}
	}
	return (false);
}

bool wifi_async_order(uint64_t id) {
	if (wifi_async_status == WIFI_ERROR && !wifi_recover()) return (false);
	if (wifi_async_status != WIFI_IDLE) { return (wifi_orders_set(id)); }
	wifi_flush_uart();
	UART_send_str("!!!O?");
	byte num[10];
	ultoa(num, id, 10);
	UART_send_str(num);
	UART_send('~');
	wifi_async_status = WIFI_BUSY;
	wifi_async_i = 0;
	wifi_curr_op = WIFI_ORDER;
	wifi_op_s_tmsp = millis();
	return (true);
}

bool wifi_async_scan(void) {
	if (wifi_async_status == WIFI_ERROR && !wifi_recover()) return (false);
	if (wifi_async_status != WIFI_IDLE) return (false);
	wifi_flush_uart();
	UART_send_str("!!!L");
	wifi_async_status = WIFI_BUSY;
	wifi_async_i = 0;
	wifi_curr_op = WIFI_SCAN;
	wifi_op_s_tmsp = millis();
	return (true);
}


bool wifi_rcv_scan(void)
{
	if (wifi_async_status != WIFI_DONE || wifi_curr_op != WIFI_SCAN)
		return (false);
	wifi_async_status = WIFI_IDLE;
	wifi_curr_op = WIFI_IDLE;
	byte str[50];
	byte i = 0;
	byte j = 0;
	byte n = 0;
	UI_list_clear();
	while (j < 512 && n < 20) {
		i = 0;
		while (i < 50 && j < 512) {
			if ((str[i++] = wifi_response[j++]) == '\n') break;
		}
		if (i == 1) break;
		str[i - 1] = 0x00;
		UI_list_set(n++, str + 2);
	}
	return (true);
}

bool wifi_rcv_order(void)
{
	if (wifi_async_status != WIFI_DONE || wifi_curr_op != WIFI_ORDER)
		return (false);
	wifi_async_status = WIFI_IDLE;
	wifi_curr_op = WIFI_IDLE;
	byte r = wifi_response[0];
	if (r == 'O')
		return (true);
	return (false);
}

bool wifi_rcv_update(void)
{
	if (wifi_async_status != WIFI_DONE || wifi_curr_op != WIFI_UPDATE)
		return (false);
	wifi_async_status = WIFI_IDLE;
	wifi_curr_op = WIFI_IDLE;
	char *rsp = wifi_response;
	if (rsp[0] == 'N')
		return (true);
	if (rsp[0] == 'E')
		return (false);
	if (rsp[0] == 'Y')
	{
		if (rsp[1] != ',')
			return (false);
		char num[10];
		int i = 2;
		int sz = 0;
		while (sz < 9)
		{
			if (rsp[i] == ',')
				break;
			num[sz++] = rsp[i++];
		}
		num[sz] = 0x00;
		i++;
		struct listItem itm;
		itm.flag = 0xFF;
		sz = 0;
		while (sz < 49)
		{
			if (rsp[i] == '\n')
			break;
			itm.name[sz++] = rsp[i++];
		}
		itm.name[sz - 1] = 0x00;
		itm.id = atol(num);
		pages_list_loaded = false;
		if (!list_add_item(itm))
			return (false);
		return (wifi_async_update());
	}
	return (false);
}


