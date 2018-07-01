/* 
 * File:   wheel.h
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 8:55 AM
 */

#ifndef WHEEL_H
#define	WHEEL_H

#include "types.h"
#include "pins.h"


void wheel_init(void);
void wheel_event(byte event);


#define WHEEL_TURN_RIGHT  1
#define WHEEL_TURN_LEFT   2
#define WHEEL_PRESS       3


#endif	/* WHEEL_H */

