#include "types.h"
#include "SPI.h"
#include "screen.h"
#include "delay.h"
#include "shiftreg.h"


#define COMMAND LOW
#define DATA	HIGH
#define OLED_SPI(x) SPI_queue_byte(x, 1)

#define OLED_RES_TRIS TRISDbits.TRISD5
#define OLED_D_C_TRIS TRISDbits.TRISD6
#define OLED_VCC_TRIS TRISDbits.TRISD7
#define OLED_RES_LAT LATDbits.LATD5
#define OLED_D_C_LAT LATDbits.LATD6
#define OLED_VCC_LAT LATDbits.LATD7

void    __ISR (_TIMER_1_VECTOR, IPL7SRS) T1_Interrupt(void)
{
	IFS0bits.T1IF = 0;				// Timer 1 interrupt flag reset
	if (slp)
		--slp;
	else
		delay_ms(0);
}

#define COMMAND LOW
#define DATA	HIGH
#define OLED_SPI(x) SPI_queue_byte(x, 1)

void	OLED_init(void)
{
	/* Assuming VDD is on */
	shiftreg_set(PIN_OLED_RST, HIGH);	// Set D5 to high
	shiftreg_set(PIN_OLED_DC, LOW);		// Set D6 to low
	shiftreg_set(PIN_OLED_13V, LOW);	// Set D7 to low
	delay_us(1);
	shiftreg_set(PIN_OLED_RST, LOW);	// Set RES# to low
	delay_us(1);
	shiftreg_set(PIN_OLED_RST, HIGH);	// Set RES# to high
	SPI_slave_select(SPI_OLED);			// Select OLED Slave
	shiftreg_set(PIN_OLED_DC, COMMAND);	// Set D6 to low
	OLED_SPI(0xFD);		// Set Command Lock
	OLED_SPI(0xAE);		// Display Off
	OLED_SPI(0xB0);		// Set Page Start Address for Page Addressing Mode,0-7
	OLED_SPI(0xC8);		// Set COM Output Scan Direction
	OLED_SPI(0x00);		// Set low column address
	OLED_SPI(0x10);		// Set high column address
	OLED_SPI(0x40);		// Set start line address
	OLED_SPI(0x81);		// Set contrast control register
	OLED_SPI(128);  	// 0-256
	OLED_SPI(0xA1);		// Set segment re-map left 0 to right 127
	OLED_SPI(0xA6);		// Set normal/inverse  display
	OLED_SPI(0xA8);		// Set multiplex ratio
	OLED_SPI(0x3F);		// (1 to 64)
	OLED_SPI(0xA4);		// Output follows RAM content
	OLED_SPI(0xD3);		// Set display vertical offset
	OLED_SPI(0x00);		// not offset
	OLED_SPI(0xD5);		// Set display clock divide ratio/oscillator frequency
	OLED_SPI(0x50);
	OLED_SPI(0xD9);		// Set pre-charge period
	OLED_SPI(0x22);
	OLED_SPI(0xDA);		// Set com pins hardware configuration
	OLED_SPI(0x12);
	OLED_SPI(0xDB);		// Set vcom high at deselect
	OLED_SPI(0x20);		// 0x20 = 0.77xVcc
	OLED_SPI(0xAD);		// Set DC-DC enable
	OLED_SPI(0x8B);		//
	OLED_SPI(0xAF);		// Turn on OLED panel

	SPI_send();
	shiftreg_set(PIN_OLED_13V, HIGH); // Set VCC to high
}

void	OLED_fill(uint8_t color)
{
	uint16_t	i;
	uint8_t		screen[1024];
	
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0x20);		// Memory Adressing Mode
	OLED_SPI(0b01);		// Vertical adressing Mode
	OLED_SPI(0x21);		// Set Column Address
	OLED_SPI(0);		// From	0 
	OLED_SPI(127);		// To	127 
	OLED_SPI(0x22);		// Set Page Address
	OLED_SPI(0);		// From 0
	OLED_SPI(7);		// To	7
	SPI_send();
	shiftreg_set(PIN_OLED_DC, DATA);
	for (i = 0; i <= 512; i++)
		OLED_SPI(color);
	SPI_send();
	for (i = 0; i <= 512; i++)
		OLED_SPI(color);
	SPI_send();
}

void	OLED_putstr_init(void)
{
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0x20);		// Memory Adressing Mode
	OLED_SPI(0b00);		// Horizontal adressing Mode
	OLED_SPI(0x21);		// Set Column Address
	OLED_SPI(0);		// From	0 
	OLED_SPI(127);		// To	127 
	OLED_SPI(0x22);		// Set Page Address
	OLED_SPI(0);		// From 0
	OLED_SPI(7);		// To	7
	OLED_SPI(0x40);		// Set Display Start Line
	SPI_send();
}

void	OLED_putstr(uint8_t *str, uint16_t offset, uint8_t spacing)
{
	uint8_t		buf[1024];
	uint8_t		tmp;
	uint16_t	j = 0;
	uint8_t		i;

	OLED_putstr_init();
	shiftreg_set(PIN_OLED_DC, DATA);
	while (str[j])
    {
		if (j + (j * spacing) >= 64)// Check if the SPI buffer is full (512B / 8)
			SPI_send();
		tmp = (str[j] - 32);		
		for(i = 0; i < 5; i++)
			OLED_SPI(OLED_characters2[tmp * 5 + i]);
		for(i = 0; i < spacing; i++)
		OLED_SPI(0x0);
		j++;
	}
	SPI_send();
}

void	OLED_wake(void)
{
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0xAF);
	SPI_send();
}

void	OLED_sleep(void)
{
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0xAE);
	SPI_send();
}