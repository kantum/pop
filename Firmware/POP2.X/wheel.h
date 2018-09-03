#ifndef WHEEL_H
#define WHEEL_H

#include "types.h"

/* PINS */
#define WHEEL_A_PORT                PORTBbits.RB9
#define WHEEL_A_TRIS                TRISBbits.TRISB9

#define WHEEL_B_PORT                PORTBbits.RB8
#define WHEEL_B_TRIS                TRISBbits.TRISB8

#define WHEEL_C_PORT                PORTBbits.RB7
#define WHEEL_C_TRIS                TRISBbits.TRISB7

void wheel_init(void);
byte wheel_get_event_timeout(size_t timeout);
byte wheel_get_event(void);

bool wheel_on_fire = 0;

#define WHEEL_NONE				0
#define WHEEL_TURN_RIGHT		1
#define WHEEL_TURN_LEFT			2
#define WHEEL_PRESS				3
#define WHEEL_LONG_PRESS		4
#define WHEEL_PRESS_TURN_RIGHT	5
#define WHEEL_PRESS_TURN_LEFT	6
#define WHEEL_PRESS_BEGIN		7
#define WHEEL_PRESS_END			8

#endif /* WHEEL_H */