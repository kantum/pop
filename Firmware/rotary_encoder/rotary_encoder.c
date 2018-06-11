/*
 * File:   main.c
 * Author: bocal
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include <p32xxxx.h>
#include <sys/attribs.h>    // contains __ISR() Macros
#include <stdio.h>
/*
 *
 */


typedef unsigned char byte;
typedef unsigned char bool;
//typedef unsigned char size_t;

#define OUTPUT  0
#define INPUT   1

#define HIGH    1
#define LOW     0

#define true    1
#define false   0

#define RISING_EDGE    1
#define FALLING_EDGE    0






#define WHEEL_TURN_RIGHT  1
#define WHEEL_TURN_LEFT   2
#define WHEEL_PRESS       3

byte wheel_turning = false;

void    __ISR (_EXTERNAL_2_VECTOR, IPL6SRS) encoderRight(void)
{
    IFS0bits.INT2IF = 0;        // External Interrupt flag reset
    if (wheel_turning == WHEEL_TURN_LEFT) {
	INTCONbits.INT3EP ^= 1;		// Swap the detecting edge
	INTCONbits.INT2EP ^= 1;		// Swap the detecting edge
	wheel_turning = false;
	T2CONbits.TON = false;		// Disable Timer 2
	wheel_event(WHEEL_TURN_LEFT);
    } else {
	wheel_turning = WHEEL_TURN_RIGHT;
        TMR2 = 0;				// Clear counter
	T2CONbits.TON = true;		// Enable Timer 2
    }

}


void    __ISR (_EXTERNAL_3_VECTOR, IPL6SRS) encoderLeft(void)
{
    IFS0bits.INT3IF = 0;        // External Interrupt flag reset
    if (wheel_turning == WHEEL_TURN_RIGHT) {
	INTCONbits.INT3EP ^= 1;		// Swap the detecting edge
	INTCONbits.INT2EP ^= 1;		// Swap the detecting edge
	wheel_turning = false;
	T2CONbits.TON = false;		// Disable Timer 2
	wheel_event(WHEEL_TURN_RIGHT);
    } else {
	wheel_turning = WHEEL_TURN_LEFT;
        TMR2 = 0;				// Clear counter
	T2CONbits.TON = true;		// Enable Timer 2
    }
}

void    __ISR (_TIMER_2_VECTOR, IPL7SRS) mainTimerInterrupt(void)
{
	IFS0bits.T2IF = 0;
	INTCONbits.INT3EP ^= 1;		// Swap the detecting edge
	INTCONbits.INT2EP ^= 1;		// Swap the detecting edge
	wheel_turning = false;
	T2CONbits.TON = false;		// Disable Timer 2

}



void wheel_event(int event) {
    if (event == WHEEL_TURN_LEFT) {
	 LATDbits.LATD7 ^= HIGH;                // Set LED OFF
 	 LATFbits.LATF1 = LOW;                // Set LED OFF

    } else {
        LATFbits.LATF1 ^= HIGH;                // Set LED ON
   	LATDbits.LATD7 = LOW;                // Set LED OFF
    }
}



void init()
{
    __builtin_disable_interrupts();        // Globally disable interrupts

    /* Input / Output Configuration */

    TRISFbits.TRISF1 = OUTPUT;            // Set LED to output
    TRISDbits.TRISD7 = OUTPUT;            // Set LED to output
    LATFbits.LATF1   = LOW;                // Set LED OFF
    LATDbits.LATD7   = LOW;                // Set LED OFF

    TRISDbits.TRISD9 = INPUT;
    TRISDbits.TRISD10 = INPUT;



     /* Rotate Right Interrupt Configuration */
    IPC2bits.INT2IP     = 6;            // Ext. Interrupt 2 Priority
    INTCONbits.INT2EP   = FALLING_EDGE;  // Set Ext. Interrupt 2 Polarity to Falling Edge
    IFS0bits.INT2IF     = 0;            // External Interrupt 2 flag reset
    IEC0bits.INT2IE     = 1;            // Interrupt Enable for Ext. Interrupt 2

    /* Rotate Left Interrupt Configuration */
    IPC3bits.INT3IP     = 6;            // Ext. Interrupt 1 Priority
    INTCONbits.INT3EP   = FALLING_EDGE; // Set Ext. Interrupt 1 Polarity to Falling Edge
    IFS0bits.INT3IF     = 0;            // External Interrupt 1 flag reset
    IEC0bits.INT3IE     = 1;            // Interrupt Enable for Ext. Interrupt 1

    /* Main Timer Configuration */
    T2CONbits.TCKPS = 0x7;		// Set pre-scale to 32
    PR2 = 9000;			// Set Timer 2 period
    TMR2 = 0;				// Clear counter
    T2CONbits.TON = false;		// Enable Timer 2

    /* Main Timer Interrupt Configuration */
    IPC2bits.T2IP = 7;			// Interrupt Priority
    IFS0bits.T2IF = 0;			// Timer 2 interrupt flag reset
    IEC0bits.T2IE = 1;			// Interrupt Enable for timer 2

    /* Set Interrupt Controller for multi-vector mode */

    INTCONSET = _INTCON_MVEC_MASK;

    __builtin_enable_interrupts();  /* Globally enable interrupts */
}


int main(int argc, char** argv)
{

    init();
    while(1);
    return (EXIT_SUCCESS);
}