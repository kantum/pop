/*
 * File:   wheel.c
 * Author: nburcion@student.42.fr
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include "wheel.h"
#include "led.h"
#include <p32xxxx.h>

volatile byte guess  = WHEEL_NONE;

volatile bool in_press_turn = false;

byte wheel_confirm_press(void) {
	delay_async_ms(3);
	while(delay_async_status()) {
		if (WHEEL_P_PORT) return (WHEEL_NONE);
	}
	delay_async_ms(500);
	bool origin_l = WHEEL_L_PORT;
	bool origin_r = WHEEL_R_PORT;
	
	while(!WHEEL_P_PORT) {
		if (!delay_async_status()) return (WHEEL_LONG_PRESS);
		if (origin_l != WHEEL_L_PORT || origin_r != WHEEL_R_PORT) {
			in_press_turn = true;
			return (WHEEL_PRESS_BEGIN);
		}
	}
	return (WHEEL_PRESS);
}

byte wheel_get_event(void) {
	return (wheel_get_event_timeout(0));
}

byte wheel_get_event_timeout(size_t timeout) {
	byte rsp = 0x00;
	size_t tme = timeout;
	bool press_en = WHEEL_P_PORT;
	bool orig_sts;
	
	if (WHEEL_P_PORT && in_press_turn) { in_press_turn = false; return (WHEEL_PRESS_END); }

	
	led_set(LED_BLUE);
	while (WHEEL_R_PORT != WHEEL_L_PORT) {
		delay_ms(3);
		if (!(tme > 3 && (tme -= 3)) && timeout) return (WHEEL_NONE);
		if (press_en && !WHEEL_P_PORT) {
			if (rsp = wheel_confirm_press()) { return (rsp); }
		}
	}
	led_set(LED_GREEN);
	if (!(tme > 3 && (tme -= 3)) && timeout) return (WHEEL_NONE);
	delay_async_ms(timeout);
	orig_sts = WHEEL_R_PORT;
	if (orig_sts){
		while (!timeout || delay_async_status()) {
			if (!WHEEL_R_PORT) { rsp = WHEEL_TURN_RIGHT; break; }
			if (!WHEEL_L_PORT) { rsp = WHEEL_TURN_LEFT; break; }
			if (press_en && !WHEEL_P_PORT) { if (rsp = wheel_confirm_press()) { break; } }
			if (WHEEL_P_PORT && in_press_turn) { in_press_turn = false; return (WHEEL_PRESS_END); }
		}
	} else {
		while (!timeout || delay_async_status()) {
			if (WHEEL_R_PORT)  { rsp = WHEEL_TURN_RIGHT; break; }
			if (WHEEL_L_PORT)  { rsp = WHEEL_TURN_LEFT; break; }
			if (press_en && !WHEEL_P_PORT) { if (rsp = wheel_confirm_press()) { break; } }
			if (WHEEL_P_PORT && in_press_turn) { in_press_turn = false; return (WHEEL_PRESS_END); }
		}
	}
	led_set(LED_RED);
	delay_ms(3);
	delay_async_ms(250);
	if (rsp == WHEEL_TURN_LEFT || rsp == WHEEL_TURN_RIGHT) {
		while (WHEEL_R_PORT != WHEEL_L_PORT && delay_async_status());
		if (orig_sts == WHEEL_R_PORT || !delay_async_status()) rsp = WHEEL_NONE;
	}
	
	if (!press_en && rsp == WHEEL_TURN_LEFT)	rsp = WHEEL_PRESS_TURN_LEFT;
	if (!press_en && rsp == WHEEL_TURN_RIGHT)  rsp = WHEEL_PRESS_TURN_RIGHT;
	
	led_set(LED_OFF);
	return (rsp);
}


void wheel_init(void)
{
	/* Input / Output Configuration */
	WHEEL_R_TRIS = INPUT;
	WHEEL_L_TRIS = INPUT;
	WHEEL_P_TRIS = INPUT;
}
