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

#define LED_OFF     0
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_WHITE   4
#define LED_YELLOW  5
#define LED_PURPLE  6
#define LED_AQUA  	7

void led_init(void);
void led_set(char status);

#endif	/* LED_H */

