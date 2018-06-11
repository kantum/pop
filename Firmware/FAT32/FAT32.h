/* 
 * File:   FAT32.h
 * Author: bocal
 *
 * Created on April 26, 2018, 8:40 AM
 */

#ifndef FAT32_H
#define	FAT32_H

bool FAT32_mount(void);
bool FAT32_mounted(void);


typedef struct  file_s {
   unsigned int cluster;
   unsigned int size;
   byte         attributes;
   unsigned int cursor;
   unsigned int cursor_sector;
}               file_t;


file_t			FAT32_ROOT_DIRECTORY;



bool            FAT32_mount(void);
bool			FAT32_fopen(file_t directory_cluster, char *filename, file_t *file);
bool            FAT32_fgetc(file_t *file, char *c);
unsigned int    FAT32_fsize(file_t *file);
bool			FAT32_fseek(file_t *file, unsigned int position);
unsigned int    FAT32_fpos(file_t *file);
bool			FAT32_filename_matches(file_t directory_cluster, char *filename);
bool            FAT32_mounted(void);
unsigned int	FAT32_cluster_to_sector(unsigned int cluster);
unsigned int	FAT32_cread_byte(unsigned int cluster, unsigned int relative_address, char *b);
unsigned int	FAT32_cread_bytes(unsigned int cluster, unsigned int start_rel_address, size_t bytes, char *b);
void			FAT32_setup_file(file_t directory, file_t *file);


#endif	/* FAT32_H */

