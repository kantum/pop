/* 
 * File:   FAT32.h
 * Author: bocal
 *
 * Created on April 26, 2018, 8:40 AM
 */

#ifndef FAT32_H
#define	FAT32_H

#include "types.h"

bool FAT32_mount(void);
bool FAT32_mounted(void);

typedef struct  file_s
{
   uint32_t	cluster;
   uint32_t	size;
   byte		attributes;
   uint32_t	cursor;
   uint32_t	cursor_sector;
}               file_t;

file_t			FAT32_ROOT_DIRECTORY;
byte            FAT32_BUFFER[512];

bool            FAT32_mount(void);
bool			FAT32_fopen(file_t directory_cluster,
							char *filename,
							file_t *file);
bool            FAT32_fgetc(file_t *file, char *c);
uint32_t	    FAT32_fsize(file_t *file);
bool			FAT32_fseek(file_t *file, uint32_t position);
uint32_t	    FAT32_fpos(file_t *file);
bool			FAT32_filename_matches(file_t directory_cluster,
										char *filename);
bool            FAT32_mounted(void);
uint32_t		FAT32_cluster_to_sector(uint32_t cluster);
uint32_t		FAT32_cread_byte(uint32_t cluster,
									uint32_t relative_address,
									char *b);
uint32_t		FAT32_cread_bytes(uint32_t cluster,
									uint32_t start_rel_address,
									size_t bytes,
									char *b);
void			FAT32_setup_file(file_t directory, file_t *file);

#endif	/* FAT32_H */

