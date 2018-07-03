/*
 * File:   wheel.c
 * Author: nburcion@student.42.fr
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include <p32xxxx.h>
#include "wheel.h"

/*
 *
 */



byte guess = WHEEL_NONE;
byte ignore = false;

void    __ISR (_EXTERNAL_2_VECTOR, IPL6SRS) encoderRight(void)
{
	IFS0bits.INT2IF = 0;        // External Interrupt flag reset
	INTCONbits.INT2EP   ^= 1; // Set Ext. Interrupt 4 Polarity to Falling Edge
	if (ignore ^= 1) {
		guess = WHEEL_TURN_RIGHT;
		TMR2 = 0;					// Clear counter
	}
}

void    __ISR (_EXTERNAL_3_VECTOR, IPL6SRS) encoderLeft(void)
{
	IFS0bits.INT3IF = 0;        // External Interrupt flag reset
	INTCONbits.INT3EP   ^= 1; // Set Ext. Interrupt 4 Polarity to Falling Edge
	if (ignore ^= 1) {
		guess = WHEEL_TURN_LEFT;
		TMR2 = 0;					// Clear counter
	}
}


void    __ISR (_EXTERNAL_4_VECTOR, IPL6SRS) encoderPush(void)
{
    IFS0bits.INT4IF = 0;        // External Interrupt flag reset
//  INTCONbits.INT4EP   ^= 1; // Set Ext. Interrupt 4 Polarity to Falling Edge
	guess = WHEEL_PRESS;
}



void    __ISR (_TIMER_2_VECTOR, IPL7SRS) mainTimerInterrupt(void)
{
	IFS0bits.T2IF = 0;
	if (guess != WHEEL_NONE) {
		wheel_event(guess);
		guess = WHEEL_NONE;
	}
}

void wheel_init(void)
{
    __builtin_disable_interrupts();        // Globally disable interrupts

    /* Input / Output Configuration */



	WHEEL_R_TRIS = INPUT;
    WHEEL_L_TRIS = INPUT;
	WHEEL_P_TRIS = INPUT;


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

	/* Push Interrupt Configuration */
    IPC4bits.INT4IP     = 6;            // Ext. Interrupt 4 Priority
    INTCONbits.INT4EP   = FALLING_EDGE; // Set Ext. Interrupt 4 Polarity to Falling Edge
    IFS0bits.INT4IF     = 0;            // External Interrupt 4 flag reset
    IEC0bits.INT4IE     = 1;            // Interrupt Enable for Ext. Interrupt 4

	
	
    /* Main Timer Configuration */
    T2CONbits.TCKPS = 0x7;		// Set pre-scale to 32
    PR2 = 10;			   	    // Set Timer 2 period
    TMR2 = 0;					// Clear counter
    T2CONbits.TON = true;		// Enable Timer 2

    /* Main Timer Interrupt Configuration */
    IPC2bits.T2IP = 7;			// Interrupt Priority
    IFS0bits.T2IF = 0;			// Timer 2 interrupt flag reset
    IEC0bits.T2IE = 1;			// Interrupt Enable for timer 2

    /* Set Interrupt Controller for multi-vector mode */

    INTCONSET = _INTCON_MVEC_MASK;

    __builtin_enable_interrupts();  /* Globally enable interrupts */
}
