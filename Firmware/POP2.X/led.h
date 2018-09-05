#include "types.h"
#include <p32xxxx.h>

#ifndef LED_H
#define LED_H

#define LED_YELLOW  0x3FF300
#define LED_RED     0x220000
#define LED_GREEN   0x002200
#define LED_BLUE    0x000022


#define LED_R_LAT   LATAbits.LATA0
#define LED_R_TRIS  TRISAbits.TRISA0

#define LED_G_LAT   LATAbits.LATA1
#define LED_G_TRIS  TRISAbits.TRISA1

#define LED_B_LAT   LATBbits.LATB13
#define LED_B_TRIS  TRISBbits.TRISB13

#define	R			2
#define	G			1
#define	B			0

extern uint16_t	led_timeout;
extern bool		led_random;

void led_init(void);
void led_set(char status);

typedef union	u_color
{
	uint32_t	hex;
	char		col[4];
}				t_color;

#endif	/* LED_H */
