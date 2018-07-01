/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on April 21, 2018, 1:02 AM
 */


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
	//delay_init();
	shiftreg_init();
	shiftreg_set(PIN_PHOTODIODE, LOW);
	//led_init();
	//wheel_init();
	SPI_init();
	//OLED_init();
	if (!SD_init())
		while(1);
	if (!FAT32_mount())
		while(1);
}

void	main(void) {
	init();
	
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
	
	
//	OLED_wake();
	/*char	*tab[] = {
		"Hello my name is POP",
		"I want to be a star",
		"But my dads are lazy",
		"So I'm still an idiot",
		"I need someone like u",
		"Do you want to sleep",
		"with me tonight ?",
		"I do not snore",
		"I swear",
		"Please",
		"Help me !!!",
		"404 error",
		"404 error",
		"404 error",
		"404 error",
		"brain not found",
		"!@#$!^%^@$&",
		"(*&)(*%@",
		"}{:_@%~!@`+_)(=",
		"AaaaAargggg ......",
		"",
		NULL,
	};
	int	i = 0;
			OLED_wake();
		for (i = 0; tab[i]; i++)
		{
			OLED_fill(0x0);
			OLED_putstr(tab[i], 10, 1);
			delay_ms(1000);
		}
		OLED_sleep();
   */
//	SPI_init();			// Initialize
	

	size_t num = 0xABCAD0BA;
	char rsp[4];
	size_t num2 = 0x00;
	
	settings_set_setting(0, 4, convert_long_to_arr(num));
	settings_get_setting(1, 4, rsp);
	num2 = convert_arr_to_long(rsp);
	
	
	
	struct listItem rndm;
	list_get_item(0, &rndm);
	
	while(1)
		WDTCONbits.WDTCLR = 1;	// Clear the watchdog
}