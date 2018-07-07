/*
 * File:   wheel.c
 * Author: nburcion@student.42.fr
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include "wheel.h"
#include "led.h"
#include <p32xxxx.h>

volatile byte	guess = WHEEL_NONE;
bool			wheel_l_slp = false;
bool			wheel_r_slp = false;

byte wheel_event(void)
{
	byte rsp = 0x00;

	led_set(LED_BLUE);
	while (WHEEL_R_PORT != WHEEL_L_PORT)
		delay_ms(3);
	led_set(LED_GREEN);
	if (WHEEL_R_PORT)
	{
		while (true)
		{
			if (!WHEEL_R_PORT)
			{
				rsp = WHEEL_TURN_RIGHT;
				break;
			}
			if (!WHEEL_L_PORT)
			{
				rsp = WHEEL_TURN_LEFT;
				break;
			}
			if (!WHEEL_P_PORT)
			{
				while (!WHEEL_P_PORT);
				rsp = WHEEL_PRESS;
				break;
			}
		}
	}
	else
	{
		while (true)
		{
			if (WHEEL_R_PORT)
			{
				rsp = WHEEL_TURN_RIGHT;
				break;
			}
			if (WHEEL_L_PORT)
			{
				rsp = WHEEL_TURN_LEFT;
				break;
			}
			if (!WHEEL_P_PORT)
			{
				while (!WHEEL_P_PORT);
				rsp = WHEEL_PRESS;
				break;
			}
		}
	}
	led_set(LED_RED);
	delay_ms(3);
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
