/*
 * File:   SPI.c
 * Author: nburcion@student.42.fr
 *
 * Created on April 2018
 */

#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

#include "SPI.h"

bool	SPI_initialized = false;			// If the SPI interface has been initialized via SPI_init();

// SPI_init: Sets up the SPI interface so it can be then used
void	SPI_init(void)
{
	byte tmp;

	SPI2CON = 0; // Stops and resets the SPI2.
	tmp = SPI2BUF; // clears the receive buffer		

	__builtin_disable_interrupts(); /* Globally disable interrupts */
	/* [SPI Receive Done Interrupt Setup] */
	IPC7bits.SPI2IP	  = 7;			/* Interrupt Priority */
	IFS1bits.SPI2RXIF = 0;			/* Reset the interrupt flag */
	IEC1bits.SPI2RXIE = 1;			/* Enable the interrupt */
	/* [/SPI Receive Done Interrupt Setup] */
	INTCONSET = _INTCON_MVEC_MASK; // Setup Interrupt controller for multi vector mode
	__builtin_enable_interrupts(); /* Globally enable interrupts */

	SPI2BRG = 0x11;			// BRG = Baud Rate Generator, SPI clock frequency for proper communication with the SD
	// Spi Clock Speed = SYSCLOCK / (2 * (SPIxBRG + 1))
	SPI2STATCLR = 0x40;		// clear the Overflow
	SPI2CON = 0x8220;		// SPI ON, 8 bits transfer, SMP=1, Master mode
	SPI2CONbits.CKP = 0;	// Set Clock Polarity idle = high active = low
	SPI2CONbits.CKE = 1;	// Set Clock Edge active\idle Clock
	// from now on, the device is ready to transmit and receive data


	SPI_initialized = true;
}

// SPI_slave_select: Activates a slave (and deactivates the others) or deactivates them all with SPI_NONE
void	SPI_slave_select(byte slave)
{
	if (slave == SPI_SD)
	{
		shiftreg_set(PIN_SD_SS, LOW);
		shiftreg_set(PIN_OLED_SS, HIGH);
	}
	else if (slave == SPI_OLED)
	{
		shiftreg_set(PIN_SD_SS, HIGH);
		shiftreg_set(PIN_OLED_SS, LOW);
	}
	else
	{				// This is for slave being SPI_NONE or as a fallback for other values
		shiftreg_set(PIN_SD_SS, HIGH);
		shiftreg_set(PIN_SD_SS, HIGH);
	}
}
// SPI_started: Returns true or false depending if the SPI protocol is on or off
bool	SPI_started(void)
{
	return (SPI_initialized);
}

// SPI_get_byte: Reads a byte from SPI and puts it in b;
bool	SPI_get_byte(byte *b)
{
	if (!SPI_available())
		return (false);		// If there are no more characters to read return false
	*b = SPI_RX[SPI_RX_i++];					// Load the next byte in b
	if (SPI_RX_i == SPI_RX_size)				// If no more unread bytes in SPI_RX buffer 'clear' buffer
		SPI_RX_i = SPI_RX_size = 0;
	return (true);								// Successful read
}

// SPI_queue_byte: Queues a byte to be sent to the SPI. Note to send the queue SPI_send has to be called.
bool	SPI_queue_byte(byte b, bool discard)
{
	if (SPI_TX_size < SPI_BUFF_SIZE)
	{			// Check there is enough space in the buffer
		SPI_TX_discard[SPI_TX_size] = discard;	// Mark or not the response byte to be discarded
		SPI_TX[SPI_TX_size++] = b;				// Put the byte into the buffer
		++SPI_TX_i;								// This instruction keeps the SPI_TX_i == SPI_TX_size so it doesn't send bytes until it's 'released' by SPI_send
		return (true);							// Byte queued successfully
	}
	else
		return (false);							// No more space in the buffer
}

// SPI_queue: Just a map for SPI_queue_byte
bool	SPI_queue(byte b)
{
	return (SPI_queue_byte(b, true));
}

// SPI_send: Sends SYNCHRONOUSLY the queued bytes through SPI
void	SPI_send(void)
{
	SPI_TX_i = 0;				// Release the 'lock' (Read SPI_queue_byte comments)
	IFS1bits.SPI2RXIF = 1;		// If it's the first byte activate the "domino" effect by setting the flag and in consequence call the interrupt function;
	while (SPI_sending()); // As the function is synchronous, wait for the bytes to be sent to return
}

// SPI_read: Sends 'bytes' times the dummy byte and stores the response in SPI_RX
bool	SPI_read(size_t bytes, byte dummy)
{
	while (bytes--)
		if (!SPI_queue_byte(dummy, false))
			return (false);
	SPI_send();
	return (true);
}

bool	SPI_get_response(size_t response_size, size_t wait_bytes, byte dummy, bool sleeping_bit, byte *response) {

	if (!SPI_read(wait_bytes, dummy))
		return (false);		// Something went wrong with the reading

	byte sleeping_byte = 0xff;							// A whole "sleeping" byte (0b11111111)
	if (!sleeping_bit)
		sleeping_byte = 0x0;			// Change to 0b00000000 if sleeping bit is 0
	byte current;										// To store the current bit
	size_t algnmt = 9;									// To store the misalignment of the response bytes
	byte previous = sleeping_bit;						// To store the previous byte
	while (wait_bytes-- > 0)
	{
		SPI_get_byte(&current);
		if (algnmt == 9)
		{								// We haven't yet started to recompose bytes
			if (current != sleeping_byte)
				algnmt = SPI_misaligned_bits(current, sleeping_bit);
		}
		else
			if (response_size && response_size--)						// If we still have bytes to deliver, do it
				*(response++) = SPI_align_bits(algnmt, previous, current);	
		previous = current;								// Shift the bytes
	}
	return (response_size == 0);
}

// [INTERNAL] Interrupt for when SPI has sent/received a byte
void    __ISR (_SPI_2_VECTOR, IPL7SRS) SPI(void)
{
	IFS1bits.SPI2RXIF = 0;									// Reset Interrupt Flag
	byte b;													// Temporary buffer for the received byte

	/* [Save received byte in queue (if any)] */
	if (SPI2STATbits.SPIRBF && SPI_RX_size < SPI_BUFF_SIZE) {
		b = SPI2BUF;										// Store the received byte temporarily
		if (SPI_TX_i && !SPI_TX_discard[SPI_TX_i - 1])		// If the response was not marked to be discarded
			SPI_RX[SPI_RX_size++] = b;						// Add the byte to the SPI_RX buffer
		if (SPI_TX_i && SPI_TX_i == SPI_TX_size)
			SPI_TX_i = SPI_TX_size = 0;						// If we have sent all the bytes, 'clear' the buffer
	}
	/* [/Save received byte in queue (if any)] */

	/* [Send Next Byte in queue (if any)] */
	if (SPI2STATbits.SPITBE && SPI_TX_i < SPI_TX_size)		// (Is buffer empty?) && (Are there any bytes on the queue?)
		SPI2BUF = SPI_TX[SPI_TX_i++];						// Actually send the byte
	/* [/Send Next Byte in queue (if any)] */
}

// [INTERNAL] SPI_sending: Checks if the SPI is still sending bytes 
bool	SPI_sending(void)
{
	return (SPI_TX_size > 0);
}

// [INTERNAL] SPI_available: Checks if there are bytes to read
bool	SPI_available(void)
{
	return (SPI_RX_i < SPI_RX_size);
}

// [INTERNAL] SPI_misaligned_bits: Calculates the misalignment for a bit
size_t	SPI_misaligned_bits(byte b, bool sleeping_bit)
{
	byte mask = 0b10000000;
	size_t misalignment = 0;
	if (sleeping_bit == 0)  { b = ~b; }
	while (mask > 0 && (mask & b) > 0) {
		misalignment++;
		mask >>= 1;
	}
	return (misalignment);
}

// [INTERNAL] SPI_align_bits: Fixes the SPI alignment problem that may arise
byte	SPI_align_bits(size_t displacement, byte b1, byte b2) {
	return ((b1 << displacement) | (b2 >> (8 - displacement)));	// Magic sauce
}
