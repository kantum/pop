#include "device.h"
#include "led.h"
#include "types.h"
#include "delay.h"
#include "UI.h"
#include "wheel.h"
#include "wifi.h"
#include "settings.h"
#include "translate.h"

bool is_unlocking = false;

void device_sleep(void)
{
    OLED_fill(0x00);
    if (wifi_async_status == WIFI_BUSY) return;
	wifi_enable(false);
	OLED_sleep();
    stop_led();

	
	PR1 = PR_MS * 5000;

	size_t n;
    byte a_ = WHEEL_A_PORT;
    byte b_ = WHEEL_B_PORT;

	while (true) {
		n = 1;
		while (n--) asm volatile("wait"); // put device in selected power-saving mode
		if (check_photo() > 0) break;
        if (WHEEL_A_PORT != a_) break;
        if (WHEEL_B_PORT != b_) break;
        if (!WHEEL_C_PORT) break;
	}
	
	PR1 = PR_MS;
	
    led_rgb(0x222222);
	//led_set(LED_BLUE);
	OLED_wake();
    led_start_random();
	wifi_enable(true);
    if (!wifi_connect(wifi_ssid, wifi_pass))
        ; // TODO: Handle error shit
	device_unlock();
}

void device_unlock(void) {
    if (is_unlocking) return;
    is_unlocking = true;
	while(!device_authorize(tr(TR_CODE_TO_UNLOCK)))
		UI_message(tr(TR_WRONG_CODE), UI_DISSMISSED_BY_ALL_EVENTS, 0);
    is_unlocking = false;
}

bool device_authorize(char *str) {
	size_t code;
	if (settings_security == 0x01) {
		code = UI_password(str, 4);
		if (code == settings_password) {
			return (true);
		} else {
			return (false);
		}
	}
	return (true);
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
