#include "types.h"

void    pps_init()
{
    /* SPI */
    TRISBbits.TRISB5 = INPUT;
    SDI1R = 0b0001;            // Set RPB5 to SDI1

    /* UART */
    TRISBbits.TRISB1 = INPUT;
    U2RXR = 0b0010;            // Set RPB1 to U2RX

    /* External Interrupt */
    TRISBbits.TRISB9 = INPUT;
    INT1R = 0b0100;            // Set RPB9 to Interrupt 1    (Button A)
    TRISBbits.TRISB8 = INPUT;
    INT3R = 0b0100;            // Set RPB8 to Interrupt 3    (Button B)
    TRISBbits.TRISB15 = INPUT;
    INT4R = 0b0011;            // Set RPB15 to Interrupt 4    (SD Switch)

	ANSELA =0;
	ANSELB = 0;
    CFGCONbits.IOLOCK = 0;     // Unlock the pps
    /* SPI */
    RPB6R = 0b0011;            // Set RPB6 to SDO1

    /* UART */
    RPB0R = 0b0010;            // Set RPB0 to U2TX

    /* Output Compare */
    //RPB3R = 0b0101;          // Set RPB3 to OC1        (Buzzer) TODO Do the buzzer without pwm
    RPA0R = 0b0101;            // Set RPA0 to OC1    (Red)
    RPA1R = 0b0101;            // Set RPA1 to OC2    (Green)
    RPB13R = 0b0101;           // Set RPB13 to OC4    (Blue)
    CFGCONbits.IOLOCK = 1;     // Lock the pps
}