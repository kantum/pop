#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

#include "types.h"
#include "UART.h"
#include "wifi.h"
#include "list.h"

char wifi_response[100];

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

char *wifi_load_response(void)
{
	int i = 0;
	byte rd;
	while (i < 100)
	{
		UART_read(&rd);
		wifi_response[i++] = rd;
		if (rd == '\n') break;
	}
	if (i == 100)
		wifi_response[i - 1] = '\n';
	return (wifi_response);
}

bool wifi_update(void)
{
	wifi_flush_uart();
	UART_send_str("!!!U");
	char *rsp = wifi_load_response();
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
		return (wifi_update());
	}
	return (false);
}

bool wifi_order(uint64_t id)
{
	wifi_flush_uart();
	UART_send_str("!!!O?");
	byte num[10];
	ultoa(num, id, 10);
	UART_send_str(num);
	UART_send('~');
	byte r;
	if (!UART_read(&r))
		return (false);
	if (r == 'O')
		return (true);
	return (false);
}
