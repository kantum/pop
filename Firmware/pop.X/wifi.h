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


#define WIFI_BUSY	0x00
#define WIFI_IDLE	0x01
#define WIFI_DONE	0x02
#define WIFI_ERROR	0x03

#define WIFI_UPDATE	0x02
#define WIFI_ORDER	0x03


byte	wifi_send_cmd(byte *cmd);
bool	wifi_disable_echo(void);
bool	wifi_check_rsp_str(byte *str);
void	wifi_flush_uart(void);
bool	wifi_start_connection(byte type, byte *str, size_t port);

bool wifi_async_is_ready(void);

bool wifi_async_update(void);
bool wifi_rcv_update(void);

bool wifi_async_order(uint64_t id);
bool wifi_rcv_order(void);


byte wifi_async_status = WIFI_IDLE;
byte wifi_curr_op = WIFI_IDLE;

#endif	/* WIFI_H */

