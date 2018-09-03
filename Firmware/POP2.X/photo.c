#include "types.h"
#include "delay.h"
#include "shiftreg.h"

#define PHOTO_ADC_PIN	AD1CHSbits.CH0SB = 12;
#define PHOTO_TRIS_PIN	TRISBbits.TRISB12 = 1;

uint16_t ADCValue;

void	photo_init(void)
{
    PHOTO_TRIS_PIN
    PHOTO_ADC_PIN
	shiftreg_set(PIN_PHOTODIODE, LOW);
}

int	check_photo(void)
{
    shiftreg_set(PIN_PHOTODIODE, HIGH);	// Light up the infrared led
    AD1CON1bits.ON = 1;					// Turn ON The ADC
    AD1CON1bits.SAMP = 1;				// Start Sampling ...
    delay_ms(10);						// During 1 ms
    AD1CON1bits.SAMP = 0;				// Start Converting
    while (!(AD1CON1bits.DONE));		// Wait for the conversion
    ADCValue = ADC1BUF0;				// Get ADC Value
    AD1CON1bits.ON = 0;					// Turn OFF The ADC
    shiftreg_set(PIN_PHOTODIODE, LOW);	// Light down the infrared led
    return ADCValue;
}
