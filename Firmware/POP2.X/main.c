#include <p32xxxx.h>
#include "types.h"
#include "FAT32.h"
#include "SD.h"
#include "SPI.h"
#include "convert.h"
#include "delay.h"
#include "led.h"
#include "list.h"
#include "screen.h"
#include "settings.h"
#include "shiftreg.h"
#include "wheel.h"
#include "UI.h"
#include "piezo.h"

void init(void)
{
	pps_init();
	delay_init();
	shiftreg_init();
	photo_init();
	led_init();
	wheel_init();
	SPI_init();
	OLED_init();
	OLED_fill(0x00);

	if (!SD_init())
	{
		delay_ms(100);
		UI_message("SD Missing or Non-Compatible", UI_IGNORE_EVENTS, 0);
		while (1);	// TODO handle error or make
	}
	if (!FAT32_mount())
	{
		delay_ms(100);
		UI_message("File System Corrupted", UI_IGNORE_EVENTS, 0);
		while (1);
	}
	settings_load();

//	OLED_set_contrast(settings_contrast);
}

void main(void)
{
	struct listItem itm;
	byte i;
	byte evnt;
	char photo_buff[12];
	uint16_t photo_dist;

	init();
	//led_set(LED_RED);
	//play_song(tetris, 400, 38);
	device_unlock();

	UI_list_clear();
	UI_message("Looking for Wi-Fi\xB0", UI_IGNORE_EVENTS, 0);
	wifi_init();
	//delay_ms(100);

	UI_message("Connecting to Wi-Fi\xB0", UI_IGNORE_EVENTS, 0);
	if (!wifi_connect("donotconnect", "pleasedont"))
		; //UI_message("ERROR Connecting to Wi-Fi", UI_IGNORE_EVENTS, 0); while(1); //TODO Handle ERROR HERE

	UI_message("Updating List\xB0", UI_IGNORE_EVENTS, 0);
	if (!wifi_async_update())
	{
		UI_message("ERROR Updating List", UI_IGNORE_EVENTS, 0);
		while (1); //TODO Handle ERROR HERE
	}
	pages_dummy_list();
//	pages_list();
	while (true);
}
