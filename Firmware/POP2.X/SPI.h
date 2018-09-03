#ifndef SPI_H
#define	SPI_H

#include "types.h"
#include "shiftreg.h"

#define SPI_BUFF_SIZE	1199
// SPI TX and RX buffer size

#define SPI_NONE    0x0         // Modes to use in the function SPI_select_slave
#define SPI_SD      0x1
#define SPI_OLED    0x2

/* SPI Globals*/
byte	SPI_TX[SPI_BUFF_SIZE];			// Outgoing SPI data buffer
bool	SPI_TX_discard[SPI_BUFF_SIZE];	// Mark if the response from the byte has to be saved
size_t	SPI_TX_size = 0;				// Allocated bytes in the Outgoing SPI data buffer
size_t	SPI_TX_i = 0;					// Internal index for the Outgoing SPI data buffer
byte	SPI_RX[SPI_BUFF_SIZE];			// Incoming SPI data buffer
size_t	SPI_RX_size = 0;				// Allocated bytes in the Outgoing SPI data buffer
size_t	SPI_RX_i = 0;					// Internal index for the Incoming SPI data buffer

/* SPI Globals */
void    SPI_init(void);
void	SPI_slave_select(byte slave);
bool	SPI_started(void);
bool	SPI_get_byte(byte *b);
bool	SPI_queue_byte(byte b, bool discard);
bool	SPI_queue(byte b);
void	SPI_send(void);
bool	SPI_read(size_t bytes, byte dummy);

// [INTERNAL]
bool	SPI_sending(void);
bool	SPI_available(void);
size_t  SPI_misaligned_bits(byte b, bool sleeping_bit);
byte    SPI_align_bits(size_t displacement, byte b1, byte b2);
bool	SPI_get_response(size_t response_size,
							size_t wait_bytes,
							byte dummy,
							bool sleeping_bit,
							byte *response);

#endif	/* SPI_H */