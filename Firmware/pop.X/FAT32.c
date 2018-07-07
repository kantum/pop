#include <p32xxxx.h>
#include "types.h"
#include "SD.h"
#include "FAT32.h"

uint32_t	FAT32_MBR_sector = 0;		// Sector of the 1st partition
uint32_t	FAT32_Data_sector = 0;
uint32_t	FAT32_FAT_sector = 0;

uint16_t	FAT32_Reserved_Sectors = 0;
byte		FAT32_Number_of_FATs = 0;
uint32_t	FAT32_FAT_Size = 0;
byte		FAT32_Sectors_per_Cluster = 0;
uint32_t	FAT32_End_of_Chain = 0;

uint32_t	FAT32_is_mounted = false;

// FAT32_mount: Mount the file system
bool	FAT32_mount(void)
{
	if (!SD_initialized()) { return (false); }
	
	byte b = 0x0; // Temporary Byte to store SD_read_byte;
	
	/*=======================[Master Boot Record]=======================*/
	if (!SD_read_byte(0x0, 0x1FE, &b) || b != 0x55) // Check MBR Signature
		return (false);	// Failed to read MBR signature
	if (!SD_read_byte(0x0, 0x1FF, &b) || b != 0xAA) // Check MBR Signature
		return (false);	// Failed to read MBR signature
	if (!SD_read_bytes(0x0, 0x1C6, 4, ((void*)(&FAT32_MBR_sector)))) // Read MBR 1st partition sector
		return (false);	// Failed to read MBR 1st partition sector
	
	/*======================[/Master Boot Record]=======================*/
	
	if (!SD_read_bytes(FAT32_MBR_sector, 0x0E, 2, (void*)(&FAT32_Reserved_Sectors)))
		return (false);	// Failed to read Number of Reserved Sectors
	if (!SD_read_byte(FAT32_MBR_sector, 0x10, &FAT32_Number_of_FATs))
		return (false);	// Failed to read Number of FATs
	if (!SD_read_bytes(FAT32_MBR_sector, 0x24, 4, ((void*)(&FAT32_FAT_Size))))
		return (false);	// Failed to read the size of a FAT
	
	uint16_t FAT32_check = 0x1;
	if (!SD_read_bytes(FAT32_MBR_sector, 0x11, 2, ((void*)(&FAT32_check))) || FAT32_check != 0x0) {
		return (false); // File System is not FAT32 (Probably is FAT16 or FAT12)
	}
	
	if (!SD_read_byte(FAT32_MBR_sector, 0x0D, &FAT32_Sectors_per_Cluster))
		return (false);	// Failed to read the number of Sectors per Cluster
	
	if (!SD_read_byte(FAT32_MBR_sector, 0x0D, &FAT32_Sectors_per_Cluster))
		return (false);	// Failed to read the number of Sectors per Cluster
	
	FAT32_Data_sector = FAT32_MBR_sector + FAT32_Reserved_Sectors + (FAT32_Number_of_FATs * FAT32_FAT_Size);
	FAT32_FAT_sector = FAT32_MBR_sector + FAT32_Reserved_Sectors;
	
	if (!SD_read_bytes(FAT32_FAT_sector, 0x04, 4, &FAT32_End_of_Chain))
		return (false);	// Failed to read the end of chain bytes
	
	FAT32_ROOT_DIRECTORY.cluster = 0x2;
	FAT32_ROOT_DIRECTORY.attributes = 0x10;
	FAT32_fseek(&FAT32_ROOT_DIRECTORY, 0x0);
	
	return (true);
}

// FAT32_fopen: Resolves the given path into a file_t
/*
 * NOTE:
 * Does not parse subdirectories!
 * Only works with short filenames i.e. 8 chars + 3 chars (extension)
 * Max file size: 512 bytes
 */
bool	FAT32_fopen(file_t directory_cluster, char *filename, file_t *file)
{
	uint32_t file_n = 0;			// Current file
	byte b;
	
	do {
		FAT32_fseek(&directory_cluster, (32 * file_n) + 0);
		if (!FAT32_fgetc(&directory_cluster, &b))
			return (false);
		if (b == 0)
			return (false);
		FAT32_fseek(&directory_cluster, (32 * file_n) + 0);	// Setting the file cursor to the beginning of the filename is required by FAT32_filename_matches
		if (FAT32_filename_matches(directory_cluster, filename)) {
			FAT32_setup_file(directory_cluster, file);
			break;
		}
	} while (++file_n);
	return (true);
}

bool	FAT32_filename_matches(file_t directory_cluster, char *filename)
{
	int i = 0;
	char c;
	
	if (directory_cluster.cursor > 0x100)
		i = 0;
	
	while (i <= 7)
	{
		if (!FAT32_fgetc(&directory_cluster, &c))
			return (false);
		if (c == ' ')
			break;
		if (c == toupper(filename[i]))
			i++;
		else
			return (false);
	}
	if (!FAT32_fgetc(&directory_cluster, &c))
		return (false);
	while (c == ' ')
		if (!FAT32_fgetc(&directory_cluster, &c)) { return (false); }
	while (c == toupper(filename[++i]))
	{
		if (!FAT32_fgetc(&directory_cluster, &c))
			break;
		if (filename[i + 1] == '\0')
			return (true);
	}
	return (false);
		
}

// FAT32_fgetc: File Get Character; (and moves the cursor) Reads char
bool	FAT32_fgetc(file_t *file, char *c)
{
	if (((file->attributes) & 0x10) != 0x10 && (file->cursor >= file->size))
		return (false);		
	if (!SD_read_byte(file->cursor_sector, ((file->cursor)++) & 511, c))
		return (false);
	if ((file->cursor & 511) == 0)
		FAT32_fseek(file, file->cursor);
	return (true);
}

// FAT32_fgetb: File Get Block; (and moves the cursor) Reads block
bool	FAT32_fgetb(file_t *file, char *b)
{
	if (!SD_read_block(file->cursor_sector++, b))
		return (false);
	file->cursor += 512;
	if ((file->cursor_sector - FAT32_Data_sector) % FAT32_Sectors_per_Cluster == 0)
		if (!FAT32_fseek(file, file->cursor)) { return (false); }
	return (true);
}

// FAT32_fputlb: File Put Last Block; Writes the last block
bool	FAT32_fputlb(file_t *file, char *b)
{
	if (!FAT32_fseek(file, file->cursor - 512)) { return (false); }
	
	if (!SD_write_sector(file->cursor_sector, b)) { return (false); }
	
	file->cursor += 512;
	if ((file->cursor_sector - FAT32_Data_sector) % FAT32_Sectors_per_Cluster == 0)
		if (!FAT32_fseek(file, file->cursor)) { return (false); }
	return (true);
}



uint32_t	FAT32_fsize(file_t *file)
{
	return (file->size);
}

bool			FAT32_fseek(file_t *file, uint32_t position)
{
	if (position > (file->size - 1))
		return (false);
	
	uint32_t sector_offst;
	uint32_t cluster_offst;
	uint32_t tmp_cluster = file->cluster;
	
//	if (relative_address < 512) {  }
	sector_offst = position / 512;
//	if (sector_offst < FAT32_Sectors_per_Cluster) { return (cluster); }
	cluster_offst = sector_offst / FAT32_Sectors_per_Cluster;
	
	while (cluster_offst && cluster_offst--)
	{
		// 128 is the number of FAT "Table Clusters" that fit in in a sector (512 / 4)
		cluster_offst = 0;
		if (!SD_read_bytes(FAT32_FAT_sector + (tmp_cluster / 128),
							4 * (tmp_cluster % 128),
							4,
							&tmp_cluster))
			return (false);
		if (tmp_cluster == FAT32_End_of_Chain)
			return (false);
	}
	position -= cluster_offst * FAT32_Sectors_per_Cluster;
	file->cursor = position;
	file->cursor_sector = FAT32_cluster_to_sector(tmp_cluster) + sector_offst;
	return (true);
}

uint32_t	FAT32_fpos(file_t *file)
{
	return (file->cursor);
}

void			FAT32_setup_file(file_t directory, file_t *file)
{	
	byte		w1;
	byte		w2;
	byte		w3;
	byte		w4;
	uint32_t	addr = directory.cursor;
	
	FAT32_fseek(&directory, addr + 0xB);
	FAT32_fgetc(&directory, &(file->attributes));
	FAT32_fseek(&directory, addr + 0x14);
	FAT32_fgetc(&directory, &w1);
	FAT32_fgetc(&directory, &w2);
	file->cluster = ((w2 << 8) | w1) << 16;
	FAT32_fseek(&directory, addr + 0x1A);
	FAT32_fgetc(&directory, &w1);
	FAT32_fgetc(&directory, &w2);
	file->cluster |= (w2 << 8) | w1;
	FAT32_fgetc(&directory, &w1);
	FAT32_fgetc(&directory, &w2);
	FAT32_fgetc(&directory, &w3);
	FAT32_fgetc(&directory, &w4);
	file->size = (w4 << 24) | (w3 << 16) | (w2 << 8) | (w1);
	FAT32_fseek(file, 0x0);
}


uint32_t	FAT32_cluster_to_sector(uint32_t cluster)
{
	return (FAT32_Data_sector + ((cluster - 2) * FAT32_Sectors_per_Cluster));
}

// FAT32_mounted: Is the file system mounted via FAT32_mount?
bool			FAT32_mounted(void)
{
	return (FAT32_is_mounted);
}
