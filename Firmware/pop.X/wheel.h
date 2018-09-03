/*
 * File:   wheel.h
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 8:55 AM
 */

#ifndef WHEEL_H
#define WHEEL_H

#include "types.h"

/* PINS */
#define WHEEL_R_PORT                PORTDbits.RD10
#define WHEEL_R_TRIS                TRISDbits.TRISD10

#define WHEEL_L_PORT                PORTDbits.RD9
#define WHEEL_L_TRIS                TRISDbits.TRISD9

#define WHEEL_P_PORT                PORTDbits.RD11
#define WHEEL_P_TRIS                TRISDbits.TRISD11

void wheel_init(void);
byte wheel_get_event_timeout(size_t timeout);
byte wheel_get_event(void);

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
