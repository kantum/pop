/* 
 * File:   shiftreg.c
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 8:55 AM
 */

#include <p32xxxx.h>
#include "shiftreg.h"



byte shiftreg_value;





void shiftreg_init(void) {
    ShiftRegisterLatch_TRIS = OUTPUT;
    ShiftRegisterLatch_LAT = LOW;
    ShiftRegisterData_TRIS = OUTPUT;
    ShiftRegisterData_LAT = LOW;
    ShiftRegisterClock_TRIS = OUTPUT;
    ShiftRegisterClock_LAT = LOW;
    shiftreg_write(0xFF);
}

void fake_delay(int n) {
	unsigned long real = 10000;
	while (real--);
}

void shiftreg_write(byte val) {
    shiftreg_value = val;
    ShiftRegisterLatch_LAT = LOW;
    int i = 0;
    byte mask = 0x1;
    while (i++ < 8) {
        ShiftRegisterData_LAT = ((shiftreg_value & mask) > 0) ? HIGH:LOW;
        ShiftRegisterClock_LAT = HIGH;
		//fake_delay(10);
        ShiftRegisterClock_LAT = LOW;
		//fake_delay(10);

        mask <<= 1;
    }
    ShiftRegisterLatch_LAT = HIGH;
}

void shiftreg_set(byte pin, bool level) {
    byte mask = 0x1 << pin;
    if (level)
        shiftreg_write(shiftreg_value | mask);
    else
        shiftreg_write(shiftreg_value & ~mask);
}


