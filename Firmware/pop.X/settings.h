/* 
 * File:   settings.h
 * Author: bocal
 *
 * Created on June 30, 2018, 6:53 AM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#define WIFI_PASS_LEN 20 

char	wifi_ssid[WIFI_PASS_LEN];
char	wifi_pass[WIFI_PASS_LEN];

bool	settings_get_wifi_credentials(void);
bool	settings_set_setting(size_t offset, size_t size, byte* val);
bool	settings_get_setting(size_t offset, size_t size, byte* val);

#endif	/* SETTINGS_H */

