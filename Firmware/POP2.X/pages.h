#ifndef PAGES_H
#define	PAGES_H

#include "types.h"
#include "UI.h"
#include "wheel.h"
#include "list.h"
#include "settings.h"
#include "convert.h"
#include "wifi.h"

#define MENU_MODE		0x00
#define MENU_SOUND		0x01
#define MENU_SECURITY	0x02
#define MENU_LANGUAGE	0x03

char	pages_list_buff[50][50];
size_t	pages_list_sz = 0;
size_t	pages_list_loaded = false;

void pages_list(void);
void pages_settings(void);
size_t pages_setting(byte menu, size_t current);

#endif	/* PAGES_H */