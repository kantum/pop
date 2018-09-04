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
	return (PHOTO_PORT_PIN * 100);
}
