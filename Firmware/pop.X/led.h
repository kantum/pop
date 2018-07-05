/* 
 * File:   led.h
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 8:25 AM
 */

#ifndef LED_H
#define	LED_H

#include "types.h"
#include "pins.h"

void led_init(void);
void led_set(char status);

#define LED_OFF     0
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_WHITE   4
#define LED_YELLOW  5
#define LED_PURPLE  6
#define LED_AQUA  	7

#define LED_R_LAT   LATDbits.LATD2
#define LED_R_TRIS  TRISDbits.TRISD2

#define LED_G_LAT   LATDbits.LATD3
#define LED_G_TRIS  TRISDbits.TRISD3

#define LED_B_LAT   LATDbits.LATD4
#define LED_B_TRIS  TRISDbits.TRISD4

#endif	/* LED_H */

