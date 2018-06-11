#include <stdbool.h>
#include <p32xxxx.h>
#include <sys/attribs.h>	// contains __ISR() Macros


#include "types.h"
#include "SPI.h"



byte shiftreg_value;

#define ShiftRegisterLatch_LAT   LATEbits.LATE2
#define ShiftRegisterLatch_TRIS  TRISEbits.TRISE2

#define ShiftRegisterData_LAT   LATEbits.LATE3
#define ShiftRegisterData_TRIS  TRISEbits.TRISE3

#define ShiftRegisterClock_LAT   LATEbits.LATE4
#define ShiftRegisterClock_TRIS  TRISEbits.TRISE4


#define PIN_A   7
#define PIN_B   6
#define PIN_C   5
#define PIN_D   4
#define PIN_E   3
#define PIN_F   2
#define PIN_G   1
#define PIN_H   0


void shiftreg_init(void) {
    ShiftRegisterLatch_TRIS = OUTPUT;
    ShiftRegisterLatch_LAT = LOW;
    ShiftRegisterData_TRIS = OUTPUT;
    ShiftRegisterData_LAT = LOW;
    ShiftRegisterClock_TRIS = OUTPUT;
    ShiftRegisterClock_LAT = LOW;
    shiftreg_write(0xFF);
}

void shiftreg_write(byte val) {
    shiftreg_value = val;
    ShiftRegisterLatch_LAT = LOW;
    int i = 0;
    byte mask = 0x1;
    while (i++ < 8) {
        ShiftRegisterData_LAT = ((shiftreg_value & mask) > 0) ? HIGH:LOW;
        ShiftRegisterClock_LAT = HIGH;
        ShiftRegisterClock_LAT = LOW;
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


int main(void)
{
    shiftreg_init();
    shiftreg_write(0x00);
    shiftreg_set(PIN_H, HIGH);
    shiftreg_set(PIN_A, HIGH);
    shiftreg_set(PIN_B, HIGH);
    shiftreg_set(PIN_H, LOW);
    shiftreg_set(PIN_A, LOW);
    shiftreg_set(PIN_B, LOW);
    while(1);
	return (0);
}
