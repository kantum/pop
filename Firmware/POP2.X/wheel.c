#include "wheel.h"
#include "led.h"
#include "delay.h"
#include "device.h"
#include <p32xxxx.h>

volatile byte guess  = WHEEL_NONE;

volatile byte wheel_turning = false;

volatile size_t wheel_pending_presses = 0;
volatile size_t wheel_pending_turns_l = 0;
volatile size_t wheel_pending_turns_r = 0;
void wheel_event(int event);

size_t last_evnt = -1;

void wheel_pending_flush(void) {
    wheel_pending_turns_l = 0;
    wheel_pending_turns_r = 0;
    wheel_pending_presses = 0;
}

byte wheel_get_event(void) {
	return (wheel_get_event_timeout(0));
}

byte wheel_get_event_timeout(size_t timeout) {	
	if (last_evnt == -1) last_evnt = millis();
//    if (wheel_pending_turns_l >= 3 && wheel_pending_turns_r == 1) {
//        wheel_pending_turns_l++;
//        wheel_pending_turns_r = 0;
//    }
//    if (wheel_pending_turns_r >= 3 && wheel_pending_turns_l == 1) {
//        wheel_pending_turns_r++;
//        wheel_pending_turns_l = 0;
//    }
    bool button_en = WHEEL_C_PORT;
    
    delay_async_ms(timeout);
    
    byte rsp = WHEEL_NONE;
    while (true)
	{
        if (wheel_pending_turns_r && wheel_pending_turns_r--)
		rsp = WHEEL_TURN_RIGHT;
        if (wheel_pending_turns_l && wheel_pending_turns_l--)
		rsp = WHEEL_TURN_LEFT;
        
        if (button_en && !WHEEL_C_PORT)
		{
            delay_ms(3);
            delay_async_ms(500);
            while (!WHEEL_C_PORT)
			{
                if (!delay_async_status())
				{
                    rsp = WHEEL_LONG_PRESS;
                    break;
                }
            }
            if (!rsp)
                rsp = WHEEL_PRESS;
        }
        if (!button_en && WHEEL_C_PORT) {
            size_t tmsp = millis() + 3;
            while (millis() != tmsp);
            if (WHEEL_C_PORT)
                button_en |= WHEEL_C_PORT;   
        }
        if (rsp) {
            last_evnt = millis();
            return (rsp);
        }
        if (timeout && !delay_async_status()) return (WHEEL_NONE);
        if (millis() - last_evnt > 20000) {
            last_evnt = millis();
            device_sleep();
            UI_request_repaint();
            return (WHEEL_NONE);
        }
    }
}

void wheel_init(void)
{
	/* Input / Output Configuration */
	WHEEL_A_TRIS = INPUT;
	WHEEL_B_TRIS = INPUT;
	WHEEL_C_TRIS = INPUT;
	
	__builtin_disable_interrupts(); // Globally disable interrupts

	/* Input / Output Configuration */

	/* Rotate Right Interrupt Configuration */
	IPC2bits.INT2IP = 6; // Ext. Interrupt 2 Priority
	IPC2bits.IC2IS = 0;
	INTCONbits.INT2EP = RISING_EDGE;  // Set Ext. Interrupt 2 to Rising Edge
	IFS0bits.INT2IF = 0; // External Interrupt 2 flag reset
	IEC0bits.INT2IE = 1; // Interrupt Enable for Ext. Interrupt 2

	/* Rotate Left Interrupt Configuration */
	IPC3bits.INT3IP = 6; // Ext. Interrupt 1 Priority
	IPC3bits.IC3IS = 0;
	INTCONbits.INT3EP = RISING_EDGE;  // Set Ext. Interrupt 1 to Rising Edge
	IFS0bits.INT3IF = 0; // External Interrupt 1 flag reset
	IEC0bits.INT3IE = 1; // Interrupt Enable for Ext. Interrupt 1

	/* Press Interrupt Configuration */
	IPC0bits.INT0IP = 6; // Ext. Interrupt 1 Priority
	IPC0bits.INT0IS = 0;
	INTCONbits.INT0EP = FALLING_EDGE;  // Set Ext. Interrupt 0 to Falling Edge
	IFS0bits.INT0IF = 0; // External Interrupt 0 flag reset
	IEC0bits.INT0IE = 1; // Interrupt Enable for Ext. Interrupt 0

	/* Set Interrupt Controller for multi-vector mode */
	INTCONSET = _INTCON_MVEC_MASK;

	__builtin_enable_interrupts(); /* Globally enable interrupts */
}

bool int2_en = true;
bool int3_en = true;

void __ISR(_EXTERNAL_2_VECTOR, IPL7SOFT) encoderRight(void)
{
	IFS0bits.INT2IF = 0; // External Interrupt flag reset
	if (WHEEL_A_PORT == HIGH) {
		// check channel A to see which way encoder is turning
		if (WHEEL_B_PORT == LOW) {
		  wheel_pending_turns_r++;          // CW
		} else {
		  wheel_pending_turns_l++;          // CCW
		}
	} else {
		// check channel B to see which way encoder is turning
		if (WHEEL_B_PORT == HIGH) {
		  wheel_pending_turns_r++;         // CW
		} else {
		  wheel_pending_turns_l++;         // CCW
		}
	}
}

void __ISR(_EXTERNAL_3_VECTOR, IPL7SOFT) encoderLeft(void)
{	
	IFS0bits.INT3IF = 0; // External Interrupt flag reset
	if (WHEEL_B_PORT == HIGH) {
		// check channel A to see which way encoder is turning
		if (WHEEL_A_PORT == LOW) {
		  wheel_pending_turns_r++;          // CW
		} else {
		  wheel_pending_turns_l++;          // CCW
		}
	} else {
		// check channel B to see which way encoder is turning
		if (WHEEL_A_PORT == HIGH) {
		  wheel_pending_turns_r++;         // CW
		} else {
		  wheel_pending_turns_l++;         // CCW
		}
	}
}

void __ISR(_EXTERNAL_0_VECTOR, IPL7SOFT) encoderPress(void)
{
	IFS0bits.INT0IF = 0;		// External Interrupt flag reset
}