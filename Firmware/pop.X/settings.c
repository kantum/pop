#include "types.h"
#include "FAT32.h"
#include "settings.h"


bool settings_get_wifi_credentials(void)
{
	file_t file;
		
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "wifi.txt", &file))
		return (false);

	byte i = 0;

	while (i < (WIFI_PASS_LEN - 1) && FAT32_fgetc(&file, wifi_ssid + i) && wifi_ssid[i++] != '\n');
	wifi_ssid[i - 1] = 0x00;
	i = 0;
	while (i < (WIFI_PASS_LEN - 1) && FAT32_fgetc(&file, wifi_pass + i) && wifi_pass[i++] != '\n');	
	wifi_pass[i] = 0x00;
	return (true);
}	

bool settings_set_setting(size_t offset, size_t size, byte* val)
{
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "config.txt", &file))
		return (false);
	
	FAT32_fgetb(&file, FAT32_BUFFER);
	while (size--) {
		FAT32_BUFFER[offset + (size)] = val[size];
	}
	return (FAT32_fputlb(&file, FAT32_BUFFER));
}

bool settings_get_setting(size_t offset, size_t size, byte* val)
{
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "config.txt", &file))
		return (false);
	
	FAT32_fgetb(&file, FAT32_BUFFER);
	while (size--) {
		val[size] = FAT32_BUFFER[offset + (size)];
	}
	return (true);
}
