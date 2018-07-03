#include "types.h"
#include "SPI.h"
#include "screen.h"
#include "delay.h"
#include "shiftreg.h"

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
	OLED_SPI(CONTRAST);	// 0-256
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
	OLED_SPI(0x01);		// Vertical adressing Mode
	OLED_SPI(0x21);		// Set Column Address
	OLED_SPI(0);		// From	0
	OLED_SPI(127);		// To	127
	OLED_SPI(0x22);		// Set Page Address
	OLED_SPI(0);		// From 0
	OLED_SPI(7);		// To	7

	SPI_send();
	shiftreg_set(PIN_OLED_DC, DATA);
	for (i = 0; i <= 1024; i++)
		OLED_SPI(color);
	SPI_send();
}

void	OLED_putstr_init(void)
{
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0x20);		// Memory Adressing Mode
	OLED_SPI(0x00);		// Horizontal adressing Mode
	OLED_SPI(0x21);		// Set Column Address
	OLED_SPI(0);		// From	0
	OLED_SPI(127);		// To	127
	OLED_SPI(0x22);		// Set Page Address
	OLED_SPI(0);		// From 0
	OLED_SPI(7);		// To	7
	OLED_SPI(0x40);		// Set Display Start Line

	SPI_send();
}

void	OLED_putstr(uint8_t *str, uint8_t offset)
{
	uint8_t		buf[1024];
	uint8_t		tmp;
	uint8_t		j;
	uint8_t		i;

	j = -1;
	shiftreg_set(PIN_OLED_DC, DATA);
	for(i = 0; i < offset; i++)
		OLED_SPI(0x0);
	while (str[++j])
    {
		tmp = (str[j] - 32);		
		for(i = 0; i < 5; i++)
			OLED_SPI(OLED_characters2[tmp * 5 + i]);
		OLED_SPI(0x0);
	}
	for(i = 0; i < 128 - (j * 6) - offset; i++)
		OLED_SPI(0x0);
	SPI_send();
}

uint8_t	scroll = 8;

void	OLED_scroll(uint8_t dir)
{
	if (dir)
		scroll++;
	else
		scroll--;
	OLED_run();
}

void	OLED_run(void)
{
	uint8_t	i;
	uint8_t	j;
	uint8_t	size;

	j = scroll;
	char	*tab[] = {
		"Hello my name is POP",
		"00000000000000000001",
		"00000000000000000002",
		"00000000000000000003",
		"00000000000000000004",
		"00000000000000000005",
		"00000000000000000006",
		"00000000000000000007",
		"00000000000000000008",
		"00000000000000000009",
		"00000000000000000010",
		"00000000000000000011",
		"00000000000000000012",
		"00000000000000000013",
		"00000000000000000014",
		"00000000000000000099",
		"Bye my name is POP",
		NULL,
	};

	OLED_wake();
	OLED_fill(0x0);
	OLED_putstr_init();
	for (size = 0; tab[size]; size++);
	for (i = 0; i < 8; i++)
	{
		if (i + j > size || i + j < 8)
			OLED_putstr("", 1);
		else
			OLED_putstr(tab[i + j - 8], 5);
	}
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
