#include "FAT32.h"


bool	images_get_from_SD(char *name, unsigned char **buff )
{
	file_t	file;
	byte	status;
	size_t	i = 0;

	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, name, &file))
		return (false);
	status = 0xFF;
	while (status == 0xFF)
	{
		if (!FAT32_fseek(&file, i))
			return (false);
		if (!FAT32_fgetc(&file, &status))
			return (false);
		i++;
	}
}
