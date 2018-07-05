/* 
 * File:   shiftreg.h
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 6:04 AM
 */

#ifndef SHIFTREG_H
#define	SHIFTREG_H

#include "types.h"
#include "pins.h"

#define ShiftRegisterLatch_LAT      LATEbits.LATE2
#define ShiftRegisterLatch_TRIS     TRISEbits.TRISE2

#define ShiftRegisterData_LAT       LATEbits.LATE3
#define ShiftRegisterData_TRIS      TRISEbits.TRISE3

#define ShiftRegisterClock_LAT      LATEbits.LATE4
#define ShiftRegisterClock_TRIS     TRISEbits.TRISE4

#define PIN_A   7
#define PIN_B   6
#define PIN_C   5
#define PIN_D   4
#define PIN_E   3
#define PIN_F   2
#define PIN_G   1
#define PIN_H   0

#define PIN_WIFI_EN		PIN_A
#define PIN_OLED_SS		PIN_B
#define PIN_OLED_RST	PIN_C
#define PIN_OLED_DC		PIN_D
#define PIN_OLED_13V	PIN_E
#define PIN_SD_SS		PIN_F
#define PIN_PHOTODIODE	PIN_G
#define PIN_WIFI_RST	PIN_H

void shiftreg_init(void);
void shiftreg_write(byte val);
void shiftreg_set(byte pin, bool level);

#endif	/* SHIFTREG_H */

