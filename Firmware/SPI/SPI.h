/* 
 * File:   SPI.h
 * Author: nburcion@student.42.fr
 *
 * Created on April 2018
 */

#ifndef SPI_H
#define	SPI_H

#include "types.h"


#define SPI_BUFF_SIZE	550		// SPI TX and RX buffer size

#define SPI_NONE    0x0         // Modes to use in the function SPI_select_slave
#define SPI_SD      0x1

#define SPI_SS_TRIS_SD   TRISFbits.TRISF1   // The 'TRIS' bit of the SD
#define SPI_SS_LAT_SD    LATFbits.LATF1     // The 'LAT' bit of the SD


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
bool	SPI_get_response(size_t response_size, size_t wait_bytes, byte dummy, bool sleeping_bit, byte *response);

#endif	/* SPI_H */

