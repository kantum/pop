#include <p32xxxx.h>
#include "types.h"
#include "delay.h"
#include "SPI.h"
#include "SD.h"
#include "FAT32.h"
#include "shiftreg.h"
#include "led.h"
#include "wheel.h"
#include "screen.h"
#include "convert.h"
#include "settings.h"
#include "list.h"

size_t times = 0;
size_t clicks = 0;
byte last_dir = 200;

void wheel_event(byte event) {
    if (event == WHEEL_TURN_RIGHT) {
		if (times < 9) { times++; }
    } else if (event == WHEEL_TURN_LEFT){
		if (times > 0) { times--; }
    }
	last_dir = event;
	delay_ms(250);
	OLED_fill(0x0);
	if (event == WHEEL_PRESS) {
		char num[2];
		num[0] = (clicks++) + '0';
		num[1] = 0;
		OLED_putstr(&num, 0, 1);
	} else {
		char num[2];
		num[0] = times + '0';
		num[1] = 0;
		OLED_putstr(&num, 0, 1);
	}
}

void	init(void)
{
	delay_init();
	shiftreg_init();
	shiftreg_set(PIN_PHOTODIODE, LOW);
	//led_init();
	//wheel_init();
	SPI_init();
	OLED_init();
//	if (!SD_init())
//		while(1);
//	if (!FAT32_mount())
//		while(1);
}

void	main(void)
{
	init();
	
	OLED_run();
	OLED_fill;
	while (42)
	{
		OLED_scroll(1);
		delay_ms(500);
		OLED_scroll(1);
		delay_ms(500);
		OLED_scroll(1);
		delay_ms(500);
		OLED_scroll(0);
		delay_ms(500);
		OLED_scroll(0);
		delay_ms(500);
		OLED_scroll(0);
		delay_ms(500);
//		OLED_img();
	}
//	led_set(LED_OFF);
//	delay_ms(1000);
//	led_set(LED_RED);
//	delay_ms(1000);
//	led_set(LED_BLUE);
//	delay_ms(1000);
//	led_set(LED_GREEN);
//	
//	UART_init(115200);
//	wifi_send_cmd("Hello World");
//	led_set(LED_PURPLE);
//	delay_ms(3000);
//	led_set(LED_OFF);
	
   
//	SPI_init();			// Initialize
	

	size_t num = 0xABCAD0BA;
	char rsp[4];
	size_t num2 = 0x00;
	
	settings_set_setting(0, 4, convert_long_to_arr(num));
	settings_get_setting(1, 4, rsp);
	num2 = convert_arr_to_long(rsp);
	
	struct listItem nw;
	
	nw.flag = 0xFF;
	nw.id = 0xACABAD00;
	nw.name[0] = 'N';
	nw.name[1] = 'e';
	nw.name[2] = 'w';
	nw.name[3] = 'l';
	nw.name[4] = 'o';
	nw.name[5] = 'w';
	nw.name[6] = 0x00;
	nw.flag = 0x88;
	list_set_item(1, nw);
	list_clear();
	nw.flag = 0xFF;
	list_add_item(nw);
	
	struct listItem rndm;
	list_get_item(1, &rndm);
	while(1)
		WDTCONbits.WDTCLR = 1;	// Clear the watchdog
}
