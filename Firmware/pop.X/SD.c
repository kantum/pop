/*
 * File:   SD.c
 * Author: nburcion@student.42.fr
 *
 * Created on April 2018
 */

#include <p32xxxx.h>

#include "types.h"
#include "SPI.h"
#include "SD.h"

static void SD_send_command(byte command,
							byte arg1,
							byte arg2,
							byte arg3,
							byte arg4,
							byte CRC);
static bool SD_read_sector(uint32_t sector);

bool SD_is_SDHC        = false; // If the SD card is SDHC (High Capacity SD)
bool SD_is_initialized = false; // If the SD card has been initialized via
                                // SD_init();
uint64_t	 SD_current_sector = 0; // The address of the sector on buffer
byte          SD_sector_buffer[512 + GRACE_BYTES]; // The buffer of the sector
byte          SD_sector_pad  = 0;     // The padding for the sector on buffer
bool          SD_good_sector = false; // If the sector on buffer is good

// SD_init: Initialize the SD Card
bool SD_init(void)
{
	uint32_t	retries;
	int			count;

	if (!SPI_started())
		return (false);
	retries = 100;
	/*========================[Set SD to SPI mode]========================*/
	//  "To do this, set the MOSI and CS lines to logic value 1"...
	SPI_slave_select(SPI_NONE);

	// ..."and toggle SD CLK for at least 74 cycles"
	count = 20;
	while (count--)
		SPI_queue(0b11111111);
	SPI_send();

	// "After the 74 cycles (or more) have occurred, your program should set the
	// CS line to 0"
	SPI_slave_select(SPI_SD);
	/*=======================[/Set SD to SPI mode]========================*/

	/*===============================[CMD0]===============================*/
	byte r1_response; // Variable to store the response
	do
	{
		SD_send_command(CMD0, 0x0, 0x0, 0x0, 0x0, 0b10010101);
		if (!(retries--))
			return (false);
		// Check that the response is correct or retry sending the CMD0
	} while (!(SPI_get_response(1, GRACE_BYTES + 1, 0xff, 1, &r1_response)
	           && r1_response == 0x1));
	/*==============================[/CMD0]===============================*/

	/*===============================[CMD8]===============================*/
	SD_send_command(CMD8, 0x0, 0x0, 0x1, 0b10101010, 0b10000111);
	//                              |     |            \_ CRC
	//                              |      \_  Check Pattern (It's arbitrary but
	//                              should be echoed back)
	//                               \_ Host Voltage (0x1 = 2.7-3.6V)

	byte r7_response[6];
	if (!SPI_get_response(6, GRACE_BYTES + 6, 0xff, 1, r7_response)
	    || r7_response[0] != 0x1 /*Status Code*/
	    || r7_response[3] != 0x1 /*Matching Voltage*/
	    || r7_response[4] != 0b10101010 /*Matching Check Pattern*/)
	{
		/* NON USABLE CARD */
		return (false);
	}
	else
	{
		// CMD 8 OK!
	}
	/*==============================[/CMD8]===============================*/

	do
	{
		/*============================[CMD55]=============================*/
		SD_send_command(CMD55, 0x0, 0x0, 0x0, 0x0, 0xff);

		if (!SPI_get_response(1, GRACE_BYTES + 1, 0xff, 1, &r1_response)
		    || r1_response != 0x1)
			return (false); // NON USABLE CARD
		else
		{
			// CMD 55 OK!
		}
		/*===========================[/CMD55]=============================*/

		/*===========================[ACMD41]=============================*/
		SD_send_command(ACMD41, 0b01000000, 0x0, 0x0, 0x0, 0xff);
		/*===========================[/ACMD41]============================*/
		if (!(retries--))
			return (false);
	}
	while (!SPI_get_response(1, GRACE_BYTES + 1, 0xff, 1, &r1_response)
	         || r1_response != 0x0);

	/*===============================[CMD58]==============================*/
	SD_send_command(CMD58, 0x0, 0x0, 0x0, 0x0, 0xff);
	if (!SPI_get_response(6, GRACE_BYTES + 1, 0xff, 1, r7_response)
	    || (r7_response[1] & 0b10000000) != 0b10000000)
		return (false);		/* CARD INIT FAILED */
	else
	{
		if ((r7_response[1] & 0b01000000) != 0b01000000)
			SD_is_SDHC = true; // Version 2.00 or later, SDHC or SHXC, SD Card
		else
			SD_is_SDHC = false; // Version 2.00 or later, Standard Capacity, SD Card
	}
	/*==============================[/CMD55]==============================*/

	/*===============================[CMD59]==============================*/
	SD_send_command(CMD59, 0x0, 0x0, 0x0, 0x0, 0xff);

	if (!SPI_get_response(1, GRACE_BYTES + 1, 0xff, 1, &r1_response)
	    || r1_response != 0x0)
		return (false); /* NON USABLE CARD */
	else
	{
		// CMD 59 OK!
	}
	/*==============================[/CMD59]=============================*/

	SD_is_initialized = true;
	return (true);
}

// SD_initialized: Is the SD initialized?
bool	SD_initialized(void)
{
	return (SD_is_initialized);
}

// SD_read_byte: Reads a byte at the specified sector and relative address and
// writes it to b
bool	SD_read_byte(uint32_t sector, uint32_t relative_address, byte* b)
{
	byte retries = 5;
	while (sector != SD_current_sector || !SD_good_sector)
	{ // If the sector is not the one on the buffer or while the sector is just
	  // bad read the sector
		if (retries == 0)
			return (false); // Put a limit on the number of tries
		SD_read_sector(sector);
		retries--;
	}
	if (relative_address < 512) // If the address is outside of the sector,
	                            // return it
		*b = SD_sector_buffer[relative_address + SD_sector_pad];
	else
		return (false);
	return (true);
}

// SD_read_bytes: Reads multiple bytes
bool	SD_read_bytes(uint32_t sector,
						uint32_t start_rel_address,
						size_t bytes,
						void* b)
{
	size_t size = bytes;
	byte   tmp;
	while (bytes > 0)
	{
		if (SD_read_byte(sector, start_rel_address + (--bytes), &tmp))
		{
			if (size == 1)
			{
				*((byte*)b) <<= 8;
				*((byte*)b) |= tmp;
			}
			else if (size == 2)
			{
				*((uint16_t*)b) <<= 8;
				*((uint16_t*)b) |= tmp;
			}
			else if (size == 4)
			{
				*((uint32_t*)b) <<= 8;
				*((uint32_t*)b) |= tmp;
			}
			else if (size == 8)
			{
				*((uint32_t*)b) <<= 8;
				*((uint32_t*)b) |= tmp;
			}
			else
			{
				while (1)
					;
			}
		}
		else
			return (false);
	}
	return (true);
}

// SD_read_block: Reads a whole sector(block) to a buffer
bool SD_read_block(uint32_t sector, byte* b)
{
	byte retries = 5;
	// If the sector is not the one on the buffer or while the sector is just
	// bad read the sector
	while (sector != SD_current_sector || !SD_good_sector)
	{
		if (retries == 0)
			return (false); // Put a limit on the number of tries
		SD_read_sector(sector);
		retries--;
	}
	int   len  = 512;
	char* buff = SD_sector_buffer + SD_sector_pad;
	while (len--) *(b++) = *(buff++);
	return (true);
}

// [INTERNAL] SD_send_command: Sends a command to the SD Card. Note you have to
// get the response by hand with SPI_get_response
static void SD_send_command(byte command,
							byte arg1,
							byte arg2,
							byte arg3,
							byte arg4,
							byte CRC)
{
	SPI_queue(command + (1 << 6)); // Command Number
	SPI_queue(arg1);               // Argument 1
	SPI_queue(arg2);               // Argument 2
	SPI_queue(arg3);               // Argument 3
	SPI_queue(arg4);               // Argument 4
	SPI_queue(CRC);                // CRC
	SPI_send();
}

// [INTERNAL] SD_read_sector: Loads a sector in a buffer
static bool SD_read_sector(uint32_t sector)
{
	int i = 0;
	SPI_slave_select(SPI_SD);
	SD_current_sector = sector;
	SD_good_sector = true; // Let's assume everything goes fine and in case any
	                       // irregularity is detected mark the sector as bad

	// Split the sector number in the 4 arguments needed by SD_send_command
	byte arg1 = sector;
	byte arg2 = (sector << 16) >> 24;
	byte arg3 = (sector << 8) >> 24;
	byte arg4 = sector >> 24;

	SD_send_command(CMD17, arg4, arg3, arg2, arg1, 0xff);

	if (!SPI_get_response(512 + GRACE_BYTES, 520 + GRACE_BYTES, 0xff, 1, SD_sector_buffer))
		SD_good_sector = false;

	if (SD_sector_buffer[0] != 0x0) // If the first response byte is not 0x0 it
	                                // means error so mark the sector as bad
		SD_good_sector = false;

	SD_sector_pad = GRACE_BYTES + 1;
	while (++i < GRACE_BYTES)
		if (SD_sector_buffer[i] == 0xfe) // Wait for a 0xfe byte in the response
			SD_sector_pad = i + 1; // The next byte is the start of the sector
			                       // data
	if (SD_sector_pad == GRACE_BYTES + 1) // If no 0xfe byte has been detected,
	                                      // then mark the sector as bad
		SD_good_sector = false;

	return (SD_good_sector);
}

bool SD_write_sector(uint32_t sector, char* buffer)
{
	SPI_slave_select(SPI_SD);

	byte r1_response;
	byte r2_response[2];
	// Split the sector number in the 4 arguments needed by SD_send_command
	byte arg1 = sector;
	byte arg2 = (sector << 16) >> 24;
	byte arg3 = (sector << 8) >> 24;
	byte arg4 = sector >> 24;

	SD_send_command(CMD24, arg4, arg3, arg2, arg1, 0xff);

	if (!SPI_get_response(1, GRACE_BYTES + 1, 0xff, 1, &r1_response)
	    || r1_response != 0x0)
		return (false);
	SPI_queue(0xff);
	if (!SPI_queue(0xfe))
		return (false);
	int len = 512;
	while (len--)
	{
		if (!SPI_queue(*(buffer++)))
			return (false);
	}
	SPI_queue(0x00); // CRC
	SPI_queue(0x00); // CRC
	SPI_send();
	if (!SPI_get_response(1, (GRACE_BYTES + 1), 0xff, 1, &r1_response))
		return (false);

	byte dummy = 0x00;
	while (dummy == 0x00) {
		SPI_read(1, 0xFF);
		SPI_get_byte(&dummy);
	}
	/*===============================[CMD13]==============================*/
	/*SD_send_command(CMD13, 0x0, 0x0, 0x0, 0x0, 0xff);
	
	SPI_read(5, 0xFF);
	while (SPI_available())
		SPI_get_byte(&dummy);
	/*if	(!SPI_get_response(2, GRACE_BYTES+2, 0xff, 1, r2_response) /*&& r2_response[0] == 0x00 && r2_response[1] == 0x00)
	{
		// NON USABLE CARD
		return (false);
	}
	else
	{
		// CMD 13 OK!
	}
	/*==============================[/CMD13]=============================*/

	return (true);
}
