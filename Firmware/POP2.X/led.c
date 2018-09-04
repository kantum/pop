#include "led.h"
#include "delay.h"

uint16_t color_len;

void stop_led()
{
	OC1CON = 0x0000; // Turn OFF OC1
	OC2CON = 0x0000; // Turn OFF OC2
	OC4CON = 0x0000; // Turn OFF OC4
}

void led_r(uint8_t color)
{
	OC1CON         = 0x0000; // Turn OFF OC1
	OC1CONbits.OCM = 0b110;  // PWM Mode Without Fault Pin
	OC1R           = PR2;    // Initialize Before Turning OC1 ON
	OC1RS          = color;  // Duty Cycle = OC1RS/(PR2 + 1) = 50%
	OC1CONbits.ON  = 1;      // Set OC1 ON (equivalent is OC1CONSET = 0x8020)
}

void led_g(uint8_t color)
{
	OC2CON         = 0x0000; // Turn OFF OC2
	OC2CONbits.OCM = 0b110;  // PWM Mode Without Fault Pin
	OC2R           = PR2;    // Initialize Before Turning OC2 ON
	OC2RS          = color;  // Duty Cycle = OC2RS/(PR2 + 1) = 50%
	OC2CONbits.ON  = 1;      // Set OC2 ON (equivalent is OC2CONSET = 0x8020)
}

void led_b(uint8_t color)
{
	OC4CON         = 0x0000; // Turn OFF OC4
	OC4CONbits.OCM = 0b110;  // PWM Mode Without Fault Pin
	OC4R           = PR2;    // Initialize Before Turning OC4 ON
	OC4RS          = color;  // Duty Cycle = OC4RS/(PR2 + 1) = 50%
	OC4CONbits.ON  = 1;      // Set OC4 ON (equivalent is OC4CONSET = 0x8020)
}

void led_rgb(uint32_t color)
{
	uint16_t pr;

	stop_led();
	pr            = SYSCLOCK / 94117 - 1; // Period = Sysclock / freq - 1
	IEC0bits.T1IE = 0;                      // Interrupt Disable for timer 1
	PR1           = PR_MS;   // Set the PR1 to match 1 ms (1000hz)
	TMR1          = 0;       // Clear counter
	T2CONbits.ON  = 0;       // Turn OFF Timer2
	T2CONbits.TCKPS = 0;     // Set Prescaler to 1
	PR2             = pr;

	led_r(color >> 16 & 0xFF);
	led_g(color >> 8 & 0xFF);
	led_b(color & 0xFF);

	T2CONbits.ON  = 1;       // Turn on Timer2
	IEC0bits.T1IE = 1;       // Interrupt Enable for timer 1
	T1CONbits.ON  = 1;       // Turn on Timer1
}

void led_init(void)
{
	LED_R_TRIS = OUTPUT;
	LED_G_TRIS = OUTPUT;
	LED_B_TRIS = OUTPUT;

	LED_R_LAT = LOW;
	LED_G_LAT = LOW;
	LED_B_LAT = LOW;
}

void	led_dim_rgb(uint32_t color1, uint32_t color2, uint16_t length)
{
	uint8_t	dim_r;
	uint8_t	dim_g;
	uint8_t	dim_b;
}
