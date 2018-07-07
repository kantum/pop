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
#include <p32xxxx.h>

void init(void)
{
	delay_init();
	shiftreg_init();
	shiftreg_set(PIN_PHOTODIODE, LOW);	// TODO photo_init();
	led_init();
	wheel_init();
	UART_init();
	wifi_init();
	SPI_init();
	SD_init();
	FAT32_mount();
	OLED_init();
}

void main(void)
{
	struct listItem itm;
	byte            i;
	byte			evnt;
	char			photo_buff[12];
	uint16_t		photo_dist;

	init();

	led_set(LED_RED);
	OLED_fill(0xFF);

	UI_list_clear();
	if (!wifi_prepare())
		UI_list_set(1, "Wifi not working");
	else
		UI_list_set(1, "Wifi working");
	if (!wifi_connect("donotconnect", "pleasedont"))
		UI_list_set(2, "Wifi not connected");
	else
		UI_list_set(2, "Wifi connected");
	if (!wifi_update())
		UI_list_set(3, "Update not working");
	else
		UI_list_set(3, "Update working");
	OLED_fill(0x0);

	UI_list_set(4, "Item4");
	UI_list_set(5, "Item5");
	UI_list_set(6, "Item6");
	UI_list_set(7, "Item7");
	UI_list_set(8, "Item8");
	UI_list_set(9, "Item9");
	i = 0;
	do
	{
		list_get_item(i, &itm);
		UI_list_set(i++, itm.name);
	}
	while (itm.flag == 0xFF);

	UI_list_start();

	while (true)
	{
		photo_dist = check_photo();
		UI_list_set(0, itoa(photo_buff, photo_dist, 10));
		UI_repaint();
		evnt = wheel_event();
		if (evnt == WHEEL_TURN_LEFT)
		{
			UI_scroll(SCROLL_UP);
			play_note(5000, 500);
		}
		else if (evnt == WHEEL_TURN_RIGHT)
		{
			UI_scroll(SCROLL_DOWN);
			play_note(5000, 500);
		}
		else if (evnt == WHEEL_PRESS)
		{
			UI_scroll(SCROLL_DOWN);
			play_note(5000, 500);
			delay_ms(250);
		}
	}
}
