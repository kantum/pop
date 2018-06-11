/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on April 21, 2018, 1:02 AM
 */


#include <p32xxxx.h>


#include "types.h"
#include "UART.h"
#include "wifi.h"

void delay_ms(size_t ms)
{
	int w = 3000000;
	while (w--);
}

int main(void) {

	if (!wifi_init())
		while (1);

	if (!wifi_join_network("Blockdays", "Matrice@42"))
		while (1);

	if (!wifi_start_connection(WIFI_TCP, "google.com", 80))
		while (1);

    wifi_send_data("GET / HTTP/1.1\r\n");
    wifi_send_data("Host: www.google.com\r\n");
    wifi_send_data("\r\n");
    
        
    UART_wait_response(20);
 
	byte buff[50];
    int i = 0;
	while (i < 50) buff[i++] = 0;
	i = 0;
	while (UART_available()) if (!UART_read(buff + i++)) return (false);

	while (true) WDTCONbits.WDTCLR = 1;
}