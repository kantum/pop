#include "types.h"
#include "delay.h"

extern uint16_t	note_len;
extern uint32_t	freq;
extern bool		buzz_on;

void	play_note(uint16_t freq, uint16_t len)
{
	uint16_t pr;
	pr = SYSCLOCK / freq - 1;	// Period = Sysclock / frequency - 1
	buzz_on = 1;
	note_len = len;
	T2CONbits.ON = 0;		 	// Turn off Timer2
	T2CONbits.TCKPS = 0;	 	// Set prescaler to 1
	PR2 = pr;
	OC1CON = 0x0000;		 	// Turn off OC1
	OC1CONbits.OCM = 0b110;	 	// PWM mode without fault pin
	OC1R = PR2 / 2;			 	// Initialize before turning OC1 on
	OC1RS = PR2 / 2;		 	// Duty cycle = OC1RS/(PR2 + 1) = 50%
	OC1CONbits.ON = 1;		 	// Set OC1 on (equivalent is OC1CONSET = 0x8020)
	T2CONbits.ON = 1;		 	// Turn on Timer2
}

void	stop_note(void)
{
	T2CONbits.ON = 0;			// Turn off Timer2
	OC1CON = 0x0000;			// Turn off OC1
	buzz_on = 0;
}
