#include "device.h"
#include "led.h"
#include "types.h"
#include "delay.h"
#include "UI.h"

#include "settings.h"

void device_sleep(void)
{
	wifi_enable(false);
	OLED_sleep();
	led_set(LED_OFF);
	
	PR1 = PR_MS * 5000;

	size_t n;
	while (true) {
		n = 100;
		while (n--) asm volatile("wait"); // put device in selected power-saving mode
		if (check_photo() > settings_distance) break;
	}
	
	PR1 = PR_MS;
	
	led_set(LED_BLUE);
	OLED_wake();
	wifi_enable(true);
	device_unlock();
}

void device_unlock(void) {
	size_t code;
	if (settings_security == 0xFF) {
		do {
			code = UI_password("Enter Code to Unlock", 4);
			if (code != settings_password) {
				UI_message("Wrong Code", UI_DISSMISSED_BY_ALL_EVENTS, 0);
			}
		} while (code != settings_password);
	}
}


void device_old_sleep(void)
{
	// Code example to put the Device in sleep and then wake the device using
	// the WDT
//	OSCCONSET = 0x10; // set Power-Saving mode to Sleep
	asm volatile ("di");
	RCONbits.IDLE = 0;
	RCONbits.SLEEP = 0;
	
	OSCCONbits.SLPEN = 1;
	
	WDTCONCLR = 0x0002; // Disable WDT window mode
	
	
	WDTCONbits.ON = HIGH;
	
	//WDTCONSET = 0x8000; // Enable WDT
	
	
	// WDT time-out period is set in the device
	// configuration
	while (check_photo() < settings_distance) {
		WDTCONSET = 0x01; // Clear the Watchdog
		asm volatile( "wait"); // put device in selected power-saving mode
		if (RCON & 0x18) // The WDT caused a wake from Sleep
		{
			asm volatile( "eret"); // return from interrupt		
		}
	}
	// code execution will resume here after wake
	// The following code fragment is at the beginning of the ?C? start-up code
	// to find whether the wake from Sleep is due to the WDT
	
	asm volatile ("ei");
}