#include "types.h"
#include "FAT32.h"
#include "settings.h"

bool settings_get_wifi_credentials(void)
{
	file_t file;
	byte i;
		
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "wifi.txt", &file))
		return (false);
	i = 0;
	while (i < (WIFI_PASS_LEN - 1)
			&& FAT32_fgetc(&file, wifi_ssid + i)
			&& wifi_ssid[i++] != '\n');
	wifi_ssid[i - 1] = 0x00;
	i = 0;
	while (i < (WIFI_PASS_LEN - 1)
			&& FAT32_fgetc(&file, wifi_pass + i)
			&& wifi_pass[i++] != '\n');	
	wifi_pass[i] = 0x00;
	return (true);
}	

bool settings_set_setting(size_t offset, size_t size, byte* val)
{
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "config.txt", &file))
		return (false);
	
	FAT32_fgetb(&file, FAT32_BUFFER);
	while (size--)
		FAT32_BUFFER[offset + (size)] = val[size];
	if (!FAT32_fputlb(&file, FAT32_BUFFER))
		return (false);
	return (true);
}

bool settings_get_setting(size_t offset, size_t size, byte* val)
{
	file_t file;
	
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "config.txt", &file))
		return (false);
	
	FAT32_fgetb(&file, FAT32_BUFFER);
	while (size--)
		val[size] = FAT32_BUFFER[offset + (size)];
	return (true);
}


bool settings_load(void) {
	if (!settings_get_setting(SETTING_MODE, &settings_mode))
		return (false)/* TODO Error Handler */;
	if (!settings_get_setting(SETTING_CONTRAST, &settings_contrast))
		return (false)/* TODO Error Handler */;
	if (!settings_get_setting(SETTING_SOUND, &settings_sound))
		return (false)/* TODO Error Handler */;
	byte rsp[2];
	if (!settings_get_setting(SETTING_DISTANCE, rsp))
		return (false)/* TODO Error Handler */;
	settings_distance = convert_arr_to_short(&rsp);
	byte rspl[4];
	if (!settings_get_setting(SETTING_PASSWORD, rspl))
		return (false)/* TODO Error Handler */;
	settings_password = convert_arr_to_long(&rspl);
	if (!settings_get_setting(SETTING_SECURITY, &settings_security))
		return (false)/* TODO Error Handler */;
	return (true);
}
