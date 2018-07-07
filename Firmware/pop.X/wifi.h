/* 
 * File:   wifi.h
 * Author: bocal
 *
 * Created on June 9, 2018, 9:21 AM
 */

#ifndef WIFI_H
#define	WIFI_H

#define CR			0x0D
#define NL			0x0A

#define WIFI_OK      1
#define WIFI_ERR     2
#define WIFI_BUS_ERR 3

#define WIFI_TCP	 0
#define WIFI_UDP	 1

byte	wifi_send_cmd(byte *cmd);
bool	wifi_disable_echo(void);
bool	wifi_check_rsp_str(byte *str);
void	wifi_flush_uart(void);
bool	wifi_start_connection(byte type, byte *str, size_t port);
void	delay_ms(size_t ms);

#endif	/* WIFI_H */

