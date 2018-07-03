#include "type.h"
#include <p32xxxx.h>		// contains device specific defines
#include <sys/attribs.h>	// contains __ISR() Macros

#define SYSCLOCK 72000000

uint16_t	note_len;
uint32_t	freq;
bool		buzz_on;
uint32_t	slp_ms;

void	stop_note(void);

void    __ISR (_TIMER_1_VECTOR, IPL7SRS) T1_Interrupt(void)
{
	IFS0bits.T1IF = 0;
	if (slp_ms)
		--slp_ms;
	if (note_len && ! --note_len)
		stop_note();
}

//void    __ISR (_TIMER_3_VECTOR, IPL7SRS) T3_Interrupt(void)
//{
//	IFS0bits.T3IF = 0;				// Reset interrupt flag
//}

void	play_note(u16 freq, uint16_t len)
{
	uint16_t pr;
	pr = SYSCLOCK / freq - 1;			// Period = Sysclock / frequency - 1
	buzz_on = 1;
	note_len = len;
	T2CONbits.ON = 0;					// Turn off Timer2
	//T2CONbits.T32 = 1;					// Set Timer2 to handle u32 PR2
	T2CONbits.TCKPS = 0;				// Set prescaler to 1
	//PR2 = SYSCLOCK / freq - 1;			// Period = Sysclock / frequency - 1
	PR2 = pr;
	OC1CON = 0x0000;					// Turn off OC1
	OC1CONbits.OCM = 0b110;				// PWM mode without fault pin
	OC1R = PR2 / 2;						// Initialize before turning OC1 on
	OC1RS = PR2 / 2;					// Duty cycle = OC1RS/(PR2 + 1) = 50%
	//OC1CONbits.OC32 = 1;				// Set OC to be 32bits compatible
	OC1CONbits.ON = 1;					// Set OC1 on (equivalent is OC1CONSET = 0x8020)
	T2CONbits.ON = 1;					// Turn on Timer2
}

void	stop_note(void)
{
	T2CONbits.ON = 0;					// Turn off Timer2
	OC1CON = 0x0000;					// Turn off OC1
	buzz_on = 0;
}

void	delay_ms(uint32_t ms)
{
	slp_ms = ms;
	while (slp_ms);
}

void	init(void)
{
	__builtin_disable_interrupts();		// Globally disable interrupts
	
	/* Set Interrupt Controller for multi-vector mode */
	INTCONSET = _INTCON_MVEC_MASK;

	T1CONbits.ON = 0;					// Turn off Timer1
	T1CONbits.TCKPS = 1;				// Set prescaler to 8
	PR1 = (SYSCLOCK / 1000) - 1;		// Set the PR1 to match 1 ms (1000hz)
	T1CONbits.ON = 1;					// Turn on Timer1

	IPC1bits.T1IP = 7;					// Interrupt Priority
	IFS0bits.T1IF = 0;					// Timer 1 interrupt flag reset
	IEC0bits.T1IE = 1;					// Interrupt Enable for timer 1

	__builtin_enable_interrupts();		/* Globally enable interrupts */
}
	
void	main(void)
{
	int note;
	init();
	while (42)
	{
		note = 3000;
		while ((note -= 100) >= 2500)
		{
			delay_ms(1000);
			play_note(note, 500);
			WDTCONbits.WDTCLR = 1;			// Clear the watchdog
		}
		if (note <= 2500)
			note = 3000;
	};
}
