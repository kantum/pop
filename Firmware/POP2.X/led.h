#include "types.h"
#include <p32xxxx.h>

#ifndef LED_H
#define LED_H

#define LED_OFF     0
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_WHITE   4
#define LED_YELLOW  5
#define LED_PURPLE  6
#define LED_AQUA  	7

#define LED_R_LAT   LATAbits.LATA0
#define LED_R_TRIS  TRISAbits.TRISA0

#define LED_G_LAT   LATAbits.LATA1
#define LED_G_TRIS  TRISAbits.TRISA1

#define LED_B_LAT   LATBbits.LATB13
#define LED_B_TRIS  TRISBbits.TRISB13

void led_init(void);
void led_set(char status);

#endif	/* LED_H */