#include "types.h"
#include "delay.h"
#include "led.h"

uint16_t	slp_ms = 0;
uint16_t	slp_us = 0;
uint16_t	note_len;
uint16_t	led_timeout;
uint32_t	freq;
bool		buzz_on;
size_t		global_millis = 0x00;

void    __ISR (_TIMER_1_VECTOR, IPL7SOFT) T1_Interrupt(void)
{
	IFS0bits.T1IF = 0;				// Timer 1 interrupt flag reset
	global_millis++;
	if (slp_us)
	{
		--slp_us;
	}
	else if (slp_ms || note_len || led_timeout)
	{
		if (slp_ms)
			--slp_ms;
		if (note_len && ! --note_len)
			stop_note();
		if (led_timeout && ! --led_timeout) {
            led_random = true;
        }
	}
}

size_t	millis() {
	return (global_millis);
}

void	delay_init()
{
	__builtin_disable_interrupts();	// Globally disable interrupts
	T1CONbits.ON = 0;				// Turn off Timer1
	T1CONbits.TCKPS = 1;			// Set prescaler to 8
	PR1 = PR_MS;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	IPC1bits.T1IP = 6;				// Interrupt Priority
	IFS0bits.T1IF = 0;				// Timer 1 interrupt flag reset
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	T1CONbits.ON = 1;				// Turn on Timer1
	INTCONSET = _INTCON_MVEC_MASK;	// Set Multi Vector Mode
	__builtin_enable_interrupts();	// Globally enable interrupts
}

void	delay_us(uint32_t us)
{
	/* ! Multipling your number by 10 */
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	PR1 = PR_US;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	slp_us = us;
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	T1CONbits.ON = 1;				// Turn on Timer1
	while (slp_us);
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	T1CONbits.ON = 0;				// Turn off Timer1
	PR1 = PR_MS;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	T1CONbits.ON = 1;				// Turn on Timer1
}

void	delay_ms(uint32_t ms)
{
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	PR1 = PR_MS;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	slp_ms = ms;
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
	T1CONbits.ON = 1;				// Turn on Timer1
 	while (slp_ms);
}

void delay_async_ms(uint32_t ms)
{
	IEC0bits.T1IE = 0;				// Interrupt Disable for timer 1
	PR1 = PR_MS;					// Set the PR1 to match 1 ms (1000hz)
	TMR1 = 0;						// Clear counter
	slp_ms = ms;
	IEC0bits.T1IE = 1;				// Interrupt Enable for timer 1
}

uint32_t delay_async_status(void)
{
	return (slp_ms);
}
