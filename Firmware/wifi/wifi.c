#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */


#include "types.h"
#include "UART.h"
#include "wifi.h"

bool wifi_init(void)
{
	UART_init(115200);
	if (!wifi_disable_echo())
		return (false);
	if (wifi_send_cmd("AT+CWMODE_CUR=1") != WIFI_OK)
		return (false);
	return (true);

}

byte wifi_send_cmd(byte *cmd)
{
	UART_send_str(cmd);
	UART_send(CR);
	UART_send(NL);
	
	byte resp = WIFI_BUS_ERR;
	byte tmp;
	
	if (!UART_read(&tmp) || tmp != CR) goto EXIT_ERR;
	if (!UART_read(&tmp) || tmp != NL) goto EXIT_ERR;
	if (!UART_read(&tmp)) return (WIFI_BUS_ERR);
	if (tmp == 'O') { // "OK" path
		resp = WIFI_OK;
		if (!wifi_check_rsp_str("K")) goto EXIT_ERR;
	} else if (tmp == 'E') { // "ERROR" path
		resp = WIFI_ERR;
		if (!wifi_check_rsp_str("RROR")) goto EXIT_ERR;
	} else { return (WIFI_BUS_ERR); }
	if (!UART_read(&tmp) || tmp != CR) goto EXIT_ERR;
	if (!UART_read(&tmp) || tmp != NL) goto EXIT_ERR;
	
	goto CLEAN_BUF;
EXIT_ERR:
	resp = WIFI_BUS_ERR;
CLEAN_BUF:
	wifi_flush_uart();
	return (resp);
}

void wifi_flush_uart(void)
{
	byte tmp;
	while(UART_available()) UART_read(&tmp);
}

bool wifi_check_rsp_str(byte *str)
{
	byte tmp;
	while (*str)
		if (!UART_read(&tmp) || tmp != *(str++)) return (false);
	return (true);
}

bool wifi_wait_rsp_byte(byte b, size_t wait_bytes)
{
    byte tmp;
	while (wait_bytes--) {
		if (!UART_read(&tmp)) return (false);
		if (tmp == b) return (true);
	}
    return (false);
}

bool wifi_start_connection(byte type, byte *str, size_t port)
{
	if (type == WIFI_TCP) {
		UART_send_str("AT+CIPSTART=\"TCP\",\"");
	} else {
		return (false);
	}
	UART_send_str(str);
	UART_send_str("\",");
    
    byte port_str[5];
    itoa(port_str, port, 10);
	UART_send_str(port_str);
	UART_send(CR); UART_send(NL);
    
    if (!wifi_check_rsp_str("CONNECT\r\n\r\nOK\r\n"))
		return (false);
	return (true);
}

bool wifi_send_data(byte *str)
{
	size_t len = 0;
	while (str[len]) len++;
	UART_send_str("AT+CIPSEND=");
   
    byte len_str[5];
    itoa(len_str, len, 10);
	UART_send_str(len_str);
	UART_send(CR); UART_send(NL);
	
    if (!wifi_check_rsp_str("\r\nOK\r\n> "))
		return (false);
	UART_send_str(str);
	if (!wifi_wait_rsp_byte('S', 25))
		return (false);
    if (!wifi_check_rsp_str("END OK\r\n"))
		return (false);
    return (true);
}

bool wifi_join_network(byte *ssid, byte *pwd)
{
	UART_send_str("AT+CWJAP_CUR=\"");
	UART_send_str(ssid);
	UART_send_str("\",\"");
	UART_send_str(pwd);
	UART_send_str("\"");
	UART_send(CR); UART_send(NL);
	if (!wifi_check_rsp_str("WIFI ")) return (false);
    byte tmp;
    if (!UART_read(&tmp)) return (false);
	if (tmp == 'D') { // "OK" path
        if (!wifi_check_rsp_str("ISCONNECT\r\nWIFI C")) return (false);
    } else if (tmp != 'C') {
        return (false);
    }
    if (!wifi_check_rsp_str("ONNECTED\r\n")) return (false);
    if (!wifi_check_rsp_str("WIFI GOT IP\r\n\r\n")) return (false);
    if (!wifi_check_rsp_str("OK\r\n")) return (false);

	return (true);
}

bool wifi_disable_echo(void)
{
	UART_send_str("ATE0");
	UART_send(CR); UART_send(NL);
    
	if (!wifi_wait_rsp_byte('O', 25)) return (false);
    if (!wifi_check_rsp_str("K\r\n")) return (false);
	return (true);
}