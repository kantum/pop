/* 
 * File:   UART.h
 * Author: bocal
 *
 * Created on June 9, 2018, 4:19 AM
 */

#ifndef UART_H
#define	UART_H


void UART_init(unsigned int baud_rate);
void UART_send(byte c);
size_t UART_available(void);
bool UART_read(byte *b);
void UART_wait_response(size_t sz);


#endif	/* UART_H */

