#include <p32xxxx.h>
#include "shiftreg.h"

byte shiftreg_value;

void shiftreg_init(void)
{
	//ANSELBbits.ANSB2 = 0;
	ShiftRegisterLatch_TRIS = OUTPUT;
	ShiftRegisterLatch_LAT  = LOW;
	//ANSELAbits.ANSA0 = 0;
	ShiftRegisterData_TRIS  = OUTPUT;
	ShiftRegisterData_LAT   = LOW;
	ShiftRegisterClock_TRIS = OUTPUT;
	ShiftRegisterClock_LAT  = LOW;
	shiftreg_write(0xFF);
}

void shiftreg_write(byte val)
{
	int  i                 = 0;
	byte mask              = 0x1;
	shiftreg_value         = val;
	ShiftRegisterLatch_LAT = LOW;
	while (i++ < 8)
	{
		ShiftRegisterData_LAT  = ((shiftreg_value & mask) > 0) ? HIGH : LOW;
		ShiftRegisterClock_LAT = HIGH;
		ShiftRegisterClock_LAT = LOW;
		mask <<= 1;
	}
	ShiftRegisterLatch_LAT = HIGH;
}

void shiftreg_set(byte pin, bool level)
{
	byte mask = 0x1 << pin;
	if (level)
		shiftreg_write(shiftreg_value | mask);
	else
		shiftreg_write(shiftreg_value & ~mask);
}