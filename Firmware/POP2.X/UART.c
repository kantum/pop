#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

#include "types.h"
#include "UART.h"

#define UART_BUFF_SIZE	512

byte	UART_RX[UART_BUFF_SIZE];	// Incoming UART data buffer
size_t	UART_RX_size = 0;			// Allocated bytes in the Outgoing UART data buffer
size_t	UART_RX_i = 0;				// Internal index for the Incoming UART data buffer

void UART_init(uint32_t baud_rate)
{
	__builtin_disable_interrupts(); /* Globally disable interrupts */
	/* UART Receive Done Interrupt Setup */
	IEC1bits.U2RXIE = 1;	/* Enable the interrupt */
	IFS1bits.U2RXIF = 0;	/* Reset the interrupt flag */
	IPC9bits.U2IP = 7;

	INTCONSET = _INTCON_MVEC_MASK; // Setup Interrupt controller for multi vector mode
	__builtin_enable_interrupts(); /* Globally enable interrupts */
	
	U2BRG  = (SYSCLOCK / (16 * baud_rate)) - 1;		//Set Baud rate 
	U2STA  = 0;
	U2MODE = 0x8000;	// Enable Uart for 8-bit data
						// no parity, 1 STOP bit (BRGH = 0 (High Baud Enable Bit))
	CM1CONbits.ON = 0;	// Disable
	CM1CONbits.ON = 0;	// Disable
	U2STASET = 0x1600;	// Enable Transmit and Receive
	size_t i = 0;
	while (i < UART_BUFF_SIZE) {
		UART_RX[i++] = 0;
	}
}

void UART_send(byte c)
{
	while(!U2STAbits.TRMT);
	U2TXREG = c;
	while(!U2STAbits.TRMT);
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
	if (UART_RX_i == UART_RX_size)
	{
		UART_RX_size = 0;
		UART_RX_i = 0;
	}
	return (true);
}

void    __ISR (_UART_2_VECTOR, IPL7SOFT) UART(void)
{
	IFS1bits.U2RXIF = 0;		// Clear the interrupt flag
	if (UART_RX_size == UART_BUFF_SIZE)
		return;
	UART_RX[UART_RX_size++] = U2RXREG;
}