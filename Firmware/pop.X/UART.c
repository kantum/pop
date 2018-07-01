/* 
 * File:   UART.c
 * Author: Nil Burcion <nburcion@student.42.fr>
 *
 * Created on April 21, 2018, 1:02 AM
 */


#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */


#include "types.h"
#include "UART.h"


#define UART_BUFF_SIZE	128

byte	UART_RX[UART_BUFF_SIZE];				// Incoming SPI data buffer
size_t	UART_RX_size = 0;					// Allocated bytes in the Outgoing SPI data buffer
size_t	UART_RX_i = 0;						// Internal index for the Incoming SPI data buffer


void UART_init(unsigned int baud_rate)
{
	
	__builtin_disable_interrupts(); /* Globally disable interrupts */
	/* [SPI Receive Done Interrupt Setup] */
	IEC0bits.U1RXIE = 1;	/* Enable the interrupt */
	IFS0bits.U1RXIF = 0;	/* Reset the interrupt flag */
	IPC6bits.U1IP = 7;
	/* [/SPI Receive Done Interrupt Setup] */
	INTCONSET = _INTCON_MVEC_MASK; // Setup Interrupt controller for multi vector mode
	__builtin_enable_interrupts(); /* Globally enable interrupts */
	
	U1BRG  = (SYSCLOCK / (16 * baud_rate)) - 1;		//Set Baud rate 
	U1STA  = 0;
	U1MODE = 0x8000;	//Enable Uart for 8-bit data
						//no parity, 1 STOP bit (BRGH = 0 (High Baud Enable Bit))
	U1STASET = 0x1400;	//Enable Transmit and Receive
}

void UART_send(byte c)
{
	while(!U1STAbits.TRMT);
	U1TXREG = c;
	while(!U1STAbits.TRMT);
}

void UART_send_str(byte *str)
{
	while (*str)
		UART_send(*(str++));
}

size_t UART_available(void)
{
	return (UART_RX_size);
}

void UART_wait_response(size_t sz)
{
	while(UART_RX_size < sz);
}

bool UART_read(byte *b)
{
	while (!UART_RX_size);
	(*b) = UART_RX[UART_RX_i++];	
	if (UART_RX_i == UART_RX_size) {
		UART_RX_size = 0;
		UART_RX_i = 0;
	}
	return (true);
}


void    __ISR (_UART_1_VECTOR, IPL7SRS) UART(void) {
	IFS0bits.U1RXIF = 0;		// Clear the interrupt flag
	if (UART_RX_size == UART_BUFF_SIZE) return;
	UART_RX[UART_RX_size++] = U1RXREG;
}
