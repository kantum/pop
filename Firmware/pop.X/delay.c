#include "types.h"
#include "delay.h"
#include "wheel.h"	// TODO change the interrupt place to avoid this include

#define PR_MS	(SYSCLOCK / 8000 - 1)
#define PR_US	(SYSCLOCK / 800000 - 1)

uint16_t	slp = 0;
uint16_t	note_len;
uint32_t	freq;
bool		buzz_on;

void    __ISR (_TIMER_1_VECTOR, IPL7SRS) T1_Interrupt(void)
{
	IFS0bits.T1IF = 0;				// Timer 1 interrupt flag reset
	if (slp)
		--slp;
	else
		delay_ms(0);
	if (note_len && ! --note_len)
		stop_note();
}

void	delay_init()
{
	__builtin_disable_interrupts();	// Globally disable interrupts
	T1CONbits.ON = 0;				// Turn off Timer1
	T1CONbits.TCKPS = 1;			// Set prescaler to 8
	PR1 = (SYSCLOCK / 8 / 1000) - 1;// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	IPC1bits.T1IP = 7;				// Interrupt Priority
	IFS0bits.T1IF = 0;				// Timer 1 interrupt flag reset
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	T1CONbits.ON = 1;				// Turn on Timer1
	/* Set Interrupt Controller for multi-vector mode */
	INTCONSET = _INTCON_MVEC_MASK;
	__builtin_enable_interrupts();	// Globally enable interrupts
}

void	delay_us(uint32_t us)
{
	/* ! Multipling your number by 10 */
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	PR1 = PR_US;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter

	slp = us;
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	while (slp);
}

void	delay_ms(uint32_t ms)
{
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	PR1 = PR_MS;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter

	slp = ms;
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1

 	while (slp);
}
