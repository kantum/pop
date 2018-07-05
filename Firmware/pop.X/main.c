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

size_t times    = 0;
size_t clicks   = 0;
byte   last_dir = 200;
byte int2_slp = 0;
byte int3_slp = 0;

void wheel_event(void)
{
//	if (event == WHEEL_PRESS)
//	{
//		if (clicks++ % 2 == 0)
//			led_set(LED_GREEN);
//		else
//			led_set(LED_OFF);
//		return;
//	}
//	times++;
//	if (last_dir != event)
//		times = 0;
//	if (times % 4 < 2)
//	{
//	if (event)
//	{
		if (event_cw)
		{
			while (event_cw-- > 0)
			{
				led_set(LED_RED);
				UI_scroll(SCROLL_DOWN);
				delay_ms(10);
			}
			event_cw = 0;
		}
		else if (event_ccw)
		{
			while (event_ccw-- > 0)
			{
				led_set(LED_BLUE);
				UI_scroll(SCROLL_UP);
				delay_ms(10);
			}
			event_ccw = 0;
		}
		event = 0;
//	}
//		last_dir = event;
//	}
//	else
//	{
//		led_set(LED_OFF);
//	}
}

void init(void)
{
	delay_init();
	shiftreg_init();
	shiftreg_set(PIN_PHOTODIODE, LOW);
	led_init();
	wheel_init();
	SPI_init();
	OLED_init();
//	SD_init();
//	FAT32_mount();
}

void main(void)

{
	init();

	OLED_fill(0x00);
//	if (!wifi_connect("donotconnect", "pleasedont"))
//		while (1);
//	if (!wifi_update())
//		while (1); 
	UI_list_clear();
	UI_list_set(0, "Item1");
	UI_list_set(1, "Item2");
	UI_list_set(2, "Item3");
	UI_list_set(3, "Item4");
	UI_list_set(4, "Item5");
	UI_list_set(5, "Item6");
	UI_list_set(6, "Item7");
	UI_list_set(7, "Item8");

//	struct listItem itm;
//	byte            i = 0;
//	do
//	{
//		list_get_item(i, &itm);
//		UI_list_set(i++, itm.name);
//	}
//	while (itm.flag == 0xFF);
//
	UI_list_start();

	while (true)
	{
		UI_repaint();
		wheel_event();
		delay_ms(100);
//		UI_scroll(SCROLL_UP);
//		delay_ms(500);
//		led_set(LED_OFF);
	}
}
