/*
 * File:   led.c
 * Author: nburcion@student.42.fr
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include "led.h"



void led_set(char status) {
	if (status == LED_OFF) {
		LED_R_LAT = LOW;
		LED_G_LAT = LOW;
		LED_B_LAT = LOW;
	} else if (status == LED_RED) {
		LED_R_LAT = HIGH;
		LED_G_LAT = LOW;
		LED_B_LAT = LOW;
	} else if (status == LED_GREEN) {
		LED_R_LAT = LOW;
		LED_G_LAT = HIGH;
		LED_B_LAT = LOW;
	} else if (status == LED_BLUE) {
		LED_R_LAT = LOW;
		LED_G_LAT = LOW;
		LED_B_LAT = HIGH;
	} else if (status == LED_WHITE) {
		LED_R_LAT = HIGH;
		LED_G_LAT = HIGH;
		LED_B_LAT = HIGH;
	} else if (status == LED_YELLOW) {
		LED_R_LAT = HIGH;
		LED_G_LAT = HIGH;
		LED_B_LAT = LOW;
	} else if (status == LED_PURPLE) {
		LED_R_LAT = HIGH;
		LED_G_LAT = LOW;
		LED_B_LAT = HIGH;
	} else if (status == LED_AQUA) {
		LED_R_LAT = LOW;
		LED_G_LAT = HIGH;
		LED_B_LAT = HIGH;
	}
}

void led_init(void) {
	LED_R_TRIS = OUTPUT;
	LED_G_TRIS = OUTPUT;
	LED_B_TRIS = OUTPUT;
	
	LED_R_LAT = LOW;
	LED_G_LAT = LOW;
	LED_B_LAT = LOW;
}