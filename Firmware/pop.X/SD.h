/* 
 * File:   SD.h
 * Author: nburcion@student.42.fr
 *
 * Created on April 23, 2018, 3:49 AM
 */

#ifndef SD_H
#define	SD_H


#define R1      1
#define R1b		0
#define R2		2
#define R3		3
#define R7		7

/* Data thanks to Chlazza: http://www.chlazza.net/sdcardinfo.html*/

#define CMD0	0	// GO_IDLE_STATE
#define CMD1	1	// SEND_OP_COND
#define CMD6	6	// SWITCH_FUNC
#define CMD8	8	// SEND_IF_COND
#define CMD9	9	// SEND_CSD
#define CMD10	10	// SEND_CID
#define CMD12	12	// STOP_TRANSMISSION
#define CMD13	13	// SEND_STATUS
#define CMD16	16	// SET_BLOCKLEN
#define CMD17	17	// READ_SINGLE_BLOCK
#define CMD18	18	// READ_MULTIPLE_BLOCK	
#define CMD24	24	// WRITE_BLOCK
#define CMD25	25	// WRITE_MULTIPLE_BLOCK
#define CMD27	27	// PROGRAM_CSD
#define CMD28	28	// SET_WRITE_PROT
#define CMD29	29	// CLR_WRITE_PROT
#define CMD30	30	// SEND_WRITE_PROT
#define CMD32	32	// ERASE_WR_BLK_START_ADDR
#define CMD33	33	// ERASE_WR_BLK_END_ADDR
#define CMD38	38	// ERASE
#define CMD42	42	// LOCK_UNLOCK
#define CMD55	55	// APP_CMD
#define CMD56	56	// GEN_CMD
#define CMD58	58	// READ_OCR
#define CMD59	59	// CRC_ON_OFF

#define ACMD13	13	// SD_STATUS
#define ACMD22	22	// SEND_NUM_WR_BLOCKS
#define ACMD23	23	// SET_WR_BLK_ERASE_COUNT
#define ACMD41	41	// SD_SEND_OP_COND
#define ACMD42	42	// SET_CLR_CARD_DETECT
#define ACMD51  51  // SEND_SCR


#define GRACE_BYTES 75  // The extra "grace" bytes that are given for SD commands and operations (This is because now our clock goes so fast we have to give the SD a nice extra time to prepare)


bool	SD_init(void);
bool	SD_initialized(void);
bool    SD_read_byte(unsigned int sector, unsigned int relative_address, byte *b);
bool	SD_read_bytes(unsigned int sector, unsigned int start_rel_address, unsigned long bytes, void *b);
bool	SD_read_block(unsigned int sector, byte *b);
bool    SD_write_sector(unsigned int sector, char *buffer);


#endif	/* SD_H */

