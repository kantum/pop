#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

#include "types.h"
#include "UART.h"
#include "wifi.h"
#include "list.h"

char wifi_response[100];
size_t wifi_async_i = 0;


bool wifi_init(void)
{
	UART_init(115200);
	delay_ms(4000);
	wifi_flush_uart();
}

bool wifi_prepare(void)
{
	byte r = 0x00;
	while (r != 'O')
	{
		UART_send_str("!!!S");
		delay_ms(100);
		if (UART_available())
		{
			UART_read(&r);
		}
		delay_ms(100);
	}
	return (true);
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
	while (UART_available() && wifi_async_i < 100)
	{
		UART_read(&rd);
		wifi_response[wifi_async_i++] = rd;
		if (rd == '\n') { wifi_async_status = WIFI_DONE; return; }
	}
	if (wifi_async_i == 100) {
		wifi_response[wifi_async_i - 1] = '\n';
		wifi_async_status = WIFI_ERROR; return;
	}
}

bool wifi_async_update(void) {
	if (wifi_async_status != WIFI_IDLE) return (false);
	wifi_flush_uart();
	UART_send_str("!!!U");
	wifi_async_status = WIFI_BUSY;
	wifi_async_i = 0;
	wifi_curr_op = WIFI_UPDATE;
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
			wifi_rcv_update(); return (true); // TODO: HANDLE ERR
		}
		if (wifi_curr_op == WIFI_ORDER) {
			wifi_rcv_order(); return (true); // TODO: HANDLE ERR
		}
	}
	return (false);
}

bool wifi_async_order(uint64_t id) {
	if (wifi_async_status != WIFI_IDLE) return (false);
	wifi_flush_uart();
	UART_send_str("!!!O?");
	byte num[10];
	ultoa(num, id, 10);
	UART_send_str(num);
	UART_send('~');
	wifi_async_status = WIFI_BUSY;
	wifi_async_i = 0;
	wifi_curr_op = WIFI_ORDER;
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
		if (!list_add_item(itm))
			return (false);
		return (wifi_async_update());
	}
	return (false);
}


