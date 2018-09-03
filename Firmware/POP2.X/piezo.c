#include "piezo.h"

extern uint16_t	note_len;
extern uint32_t	freq;
extern bool		buzz_on;

void	stop_note(void)
{
	T2CONbits.ON = 0;			// Turn OFF Timer2
	OC1CON = 0x0000;			// Turn OFF OC1
	buzz_on = 0;
}

void	play_note(uint16_t freq, uint16_t len)
{
	uint16_t pr;
	stop_note();
	if (settings_sound != 0x01)
		return;
	pr = (uint16_t)(SYSCLOCK / freq - 1);	// Period = Sysclock / frequency - 1
	buzz_on = 1;
	note_len = len;
	IEC0bits.T1IE = 0;			// Interrupt Disable for timer 1
	PR1 = PR_MS;				// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;					// Clear counter

	T2CONbits.ON = 0;		 	// Turn OFF Timer2
	T2CONbits.TCKPS = 0;	 	// Set Prescaler to 1
	PR2 = pr;
	OC1CON = 0x0000;		 	// Turn OFF OC1
	OC1CONbits.OCM = 0b110;	 	// PWM Mode Without Fault Pin
	OC1R = PR2 / 2;			 	// Initialize Before Turning OC1 ON
	OC1RS = PR2 / 2;		 	// Duty Cycle = OC1RS/(PR2 + 1) = 50%
	OC1CONbits.ON = 1;		 	// Set OC1 ON (equivalent is OC1CONSET = 0x8020)
	T2CONbits.ON = 1;		 	// Turn on Timer2
	IEC0bits.T1IE = 1;			// Interrupt Enable for timer 1
	T1CONbits.ON = 1;			// Turn on Timer1
}

void	play_song(note_t *array, uint16_t speed, size_t size)
{
	size_t	i;

	for (i = 0; i < size; i++)
	{
		play_note(array[i].freq, array[i].len * speed);
		delay_ms(array[i].sil * speed);
	}
}