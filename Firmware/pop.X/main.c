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

size_t times = 0;
byte last_dir = 200;

void wheel_event(byte event) {
	if (last_dir != event) { times = 0; }
    if (event == WHEEL_TURN_LEFT) {
		if ((times++) % 2) {
			led_set(LED_BLUE);
		} else {
			led_set(LED_OFF);
		}
    } else if (event == WHEEL_TURN_RIGHT){
        if ((times++) % 2) {
			led_set(LED_GREEN);
		} else {
			led_set(LED_OFF);
		}
    } else if (event == WHEEL_PRESS) {
		led_set(LED_RED);
	}
	last_dir = event;
}

void	init(void)
{
	delay_init();
	shiftreg_init();
//	shiftreg_set(PIN_PHOTODIODE, LOW);
//	led_init();
//	wheel_init();
	SPI_init();
	OLED_init();
}

void	main(void) {
	init();

	char	*tab[] = {
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
			OLED_putstr(tab[i], 0, 1);
			delay_ms(1000);
		}
		OLED_sleep();
	while(42)
	{	

	//	WDTCONbits.WDTCLR = 1;	// Clear the watchdog
	}	
//    
//	SPI_init();			// Initialize
//	
//	if (!SD_init())		// Initialize the SD Interface
//		while(1);
//	
//	if (!FAT32_mount())
//		while(1);
//
//		
//	file_t file;
//		
//	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, "lipsum.txt", &file))
//		while(1);
//
//	char contents[512];
//	
//	if (!FAT32_fgetb(&file, contents))
//		while(1);
//
//		
//	while(1)
//		WDTCONbits.WDTCLR = 1;	// Clear the watchdog
}