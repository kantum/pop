#include "types.h"
#include "FAT32.h"
#include "list.h"




bool list_set_item(size_t index, struct listItem item) {
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "list.txt", &file))
		return (false);
	if (!FAT32_fseek(&file, 512 * index))
		return (false);
	if (!FAT32_fgetb(&file, FAT32_BUFFER))
		return (false);
	
	size_t i = 0;
	size_t sz = 0;
	FAT32_BUFFER[i++] = item.flag;
	sz = 0;
	while (sz < 50 && item.name[sz]) {
		FAT32_BUFFER[i++] = item.name[sz++];
	}
	while (sz++ < 50) {
		FAT32_BUFFER[i++] = 0x00;
	}
	byte *item_id = (byte *)convert_long_to_arr(item.id);
	sz = 0;
	while (sz < 4) {
		FAT32_BUFFER[i++] = item_id[sz++];
	}
	while (i < 512) {
		FAT32_BUFFER[i++] = 0x00;
	}
	return (FAT32_fputlb(&file, FAT32_BUFFER));
}


bool list_get_item(size_t index, struct listItem *item) {
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "list.txt", &file))
		return (false);
	if (!FAT32_fseek(&file, 512 * index))
		return (false);
	if (!FAT32_fgetb(&file, FAT32_BUFFER))
		return (false);
	
	size_t i = 0;
	size_t sz = 0;
	item->flag = FAT32_BUFFER[i++];
	sz = 0;
	while (sz < 50) {
		item->name[sz++] = FAT32_BUFFER[i++];
	}
	item->id = convert_arr_to_long(FAT32_BUFFER + i);
	return (true);
}

bool list_add_item(struct listItem item) {
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "list.txt", &file))
		return (false);
	byte status = 0x1;
	size_t i = 0;
	while(status) {
		if (!FAT32_fseek(&file, 512 * i))
			return (false);
		if (!FAT32_fgetc(&file, &status))
			return (false);
		i++;
	}
	i--;
	struct listItem end_itm;
	
	end_itm.flag = 0x00;
	end_itm.name[0] = 0x00;
	
	delay_ms(10);
	if (!list_set_item(i, item))
		return (false);
	delay_ms(10);
	if (!list_set_item(i + 1, end_itm))
		return (false);
	return (true);
}


bool list_clear(void) {
	struct listItem end_itm;
	
	end_itm.flag = 0x00;
	end_itm.name[0] = 0x00;
	
	
	return (list_set_item(0, end_itm));
}