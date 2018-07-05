/*
 * File:   wheel.c
 * Author: nburcion@student.42.fr
 *
 * Created on May 23, 2018, 6:26 PM
 */

#include "wheel.h"
#include "UI.h"
#include <p32xxxx.h>

bool	A;		// Right
bool	B;		// Left
bool	state;
bool	first;
byte	event = WHEEL_NONE;
byte	event_cw = 0;
byte	event_ccw = 0;
//byte	int_slp1;
//byte	int_slp2;

void __ISR(_EXTERNAL_2_VECTOR, IPL6SRS) encoderRight(void)	// A
{
	IFS0bits.INT2IF = 0;    // External Interrupt flag reset
	INTCONbits.INT2EP ^= 1; // Switch Polarity
//	state ^= 1;
	IEC0bits.INT2IE = 0;    // Stop Interrupt
	int2_slp = 2;			// For 1 millisecond

	if (first)
	{
		//event = WHEEL_TURN_LEFT;
		++event_cw;
		first = 0;
	}
	else
	{
		first = 1;
	}
//	if (state == 1 && WHEEL_L_PORT == 1)
//	{
//		event = WHEEL_TURN_RIGHT;
//	}
//	else if (state == 1 && WHEEL_L_PORT == 0)
//	{
//		state = 0;
//		event = WHEEL_TURN_LEFT;
//	}
//	else if (state == 0 && WHEEL_L_PORT == 1)
//	{
//		state = 1;
//		event = WHEEL_TURN_LEFT;
//	}
//	else if (state == 0 && WHEEL_L_PORT == 0)
//	{
//		event = WHEEL_TURN_RIGHT;
//	}
//	while (!(WHEEL_R_PORT == WHEEL_L_PORT));
}

void __ISR(_EXTERNAL_3_VECTOR, IPL6SRS) encoderLeft(void)	// B
{
	IFS0bits.INT3IF = 0;    // External Interrupt flag reset
	INTCONbits.INT3EP ^= 1; // Switch Polarity
//	state ^= 1;
	IEC0bits.INT3IE = 0;    // Stop Interrupt
	int3_slp = 2;

	if (first)
	{
		//event = WHEEL_TURN_RIGHT;
		++event_ccw;
		first = 0;
	}
	else
	{
		first = 2;
	}
//	if (state == 1 && WHEEL_R_PORT == 1)
//	{
//		event = WHEEL_TURN_LEFT;
//	}
//	else if (state == 1 && WHEEL_R_PORT == 0)
//	{
//		state = 0;
//		event = WHEEL_TURN_RIGHT;
//	}
//	else if (state == 0 && WHEEL_R_PORT == 1)
//	{
//		state = 1;
//		event = WHEEL_TURN_RIGHT;
//	}
//	else if (state == 0 && WHEEL_R_PORT == 0)
//	{
//		event = WHEEL_TURN_LEFT;
//	}
//	while (!(WHEEL_R_PORT == WHEEL_L_PORT));
}

void __ISR(_EXTERNAL_4_VECTOR, IPL6SRS) encoderPush(void)
{
	IFS0bits.INT4IF = 0; // External Interrupt flag reset
	//  INTCONbits.INT4EP   ^= 1; // Set Ext. Interrupt 4 Polarity to Falling
	//  Edge
}

//void __ISR(_TIMER_2_VECTOR, IPL7SRS) mainTimerInterrupt(void)
//{
//	IFS0bits.T2IF = 0;
//	if (guess != WHEEL_NONE)
//	{
//		wheel_event(guess);
//		guess = WHEEL_NONE;
//	}
//}

void wheel_init(void)
{
	A		= 1;
	B		= 1;
	state	= 1;

	__builtin_disable_interrupts(); // Globally disable interrupts

	/* Input / Output Configuration */
	WHEEL_R_TRIS = INPUT;
	WHEEL_L_TRIS = INPUT;
	WHEEL_P_TRIS = INPUT;
	/* Rotate Right Interrupt Configuration */
	IPC2bits.INT2IP   = 6;            // Ext. Interrupt 2 Priority
	INTCONbits.INT2EP = FALLING_EDGE; // Set Ext. Interrupt 2 Polarity to
	                                  // Falling Edge
	IFS0bits.INT2IF = 0;              // External Interrupt 2 flag reset
	IEC0bits.INT2IE = 1;              // Interrupt Enable for Ext. Interrupt 2
	/* Rotate Left Interrupt Configuration */
	IPC3bits.INT3IP   = 6;            // Ext. Interrupt 3 Priority
	INTCONbits.INT3EP = FALLING_EDGE; // Set Ext. Interrupt 3 Polarity to
	                                  // Falling Edge
	IFS0bits.INT3IF = 0;              // External Interrupt 3 flag reset
	IEC0bits.INT3IE = 1;              // Interrupt Enable for Ext. Interrupt 3

	/* Push Interrupt Configuration */
	IPC4bits.INT4IP   = 6;            // Ext. Interrupt 4 Priority
	INTCONbits.INT4EP = FALLING_EDGE; // Set Ext. Interrupt 4 Polarity to
	                                  // Falling Edge
	IFS0bits.INT4IF = 0;              // External Interrupt 4 flag reset
	IEC0bits.INT4IE = 1;              // Interrupt Enable for Ext. Interrupt 4

	__builtin_enable_interrupts(); /* Globally enable interrupts */
}
