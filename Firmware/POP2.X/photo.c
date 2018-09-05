#include "types.h"
#include "delay.h"
#include "shiftreg.h"

#define PHOTO_PORT_PIN	PORTBbits.RB12
#define PHOTO_TRIS_PIN	TRISBbits.TRISB12

void	photo_init(void)
{
    PHOTO_TRIS_PIN = INPUT;
	shiftreg_set(PIN_PHOTODIODE, LOW);
}

int	check_photo(void)
{
    shiftreg_set(PIN_PHOTODIODE, HIGH);
    delay_ms(1);
    int val = PHOTO_PORT_PIN * 100;
    shiftreg_set(PIN_PHOTODIODE, LOW);
	return (val);
}
