#include "types.h"
#include "delay.h"
#include "shiftreg.h"

#define PHOTO_ADC_PIN	AD1CHSbits.CH0SA = 12;
#define PHOTO_TRIS_PIN	TRISBbits.TRISB12 = 1;

uint16_t ADCValue;

int	check_photo(void)
{
    shiftreg_set(PIN_PHOTODIODE, HIGH);	// Light up the infrared led
    PHOTO_TRIS_PIN
    PHOTO_ADC_PIN
    AD1CON1bits.ADON = 1;				// Turn ON The ADC
    AD1CON1SET = 0x0002;				// Start Sampling ...
    delay_ms(10);						// During 1 ms
    AD1CON1CLR = 0x0002;				// Start Converting
    while (!(AD1CON1 & 0x0001));		// Wait for the conversion
    ADCValue = ADC1BUF0;				// Get ADC Value
    AD1CON1bits.ADON = 0;				// Turn OFF The ADC
    shiftreg_set(PIN_PHOTODIODE, LOW);	// Light down the infrared led
    return ADCValue;
}
