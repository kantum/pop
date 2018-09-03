#include "types.h"
#include "SPI.h"
#include "screen.h"
#include "delay.h"
#include "shiftreg.h"
#include "FAT32.h"
#include "SD.h"
#include "wifi.h"

byte OLED_page = 0;

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
	OLED_SPI(0x50);		// <-------- 0x50
	OLED_SPI(0xD9);		// Set pre-charge period
	OLED_SPI(0x22);		// <-------- 0x22
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

void	OLED_set_contrast(byte contrast)
{
	// This does the mapping between 0-100 and 0-255
	if (contrast <= 100) contrast = (float)contrast * 2.55;
	
	SPI_slave_select(SPI_OLED);
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0x81);							// Set contrast control register
	OLED_SPI(contrast);						// 0-256
	SPI_send();
}

void	OLED_fill(byte color)
{
	uint16_t	i;
	byte		screen[1024];
	
	SPI_slave_select(SPI_OLED);
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
	OLED_page = 0;
}

void	OLED_putstr_init(void)
{
	SPI_slave_select(SPI_OLED);
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
	OLED_page = 0;
}

void	OLED_filler(byte i, byte options)
{
	byte filler = 0x00;
	if (options & OLED_FONT_TRANSPARENT)
		filler = FAT32_BUFFER[128 * (OLED_page % 4) + i];
	if (options & OLED_FONT_INVERTED)
		OLED_SPI(~filler);
	else
		OLED_SPI(filler);
}

void	OLED_putbuff(byte *buff)
{
	SPI_slave_select(SPI_OLED);
	shiftreg_set(PIN_OLED_DC, DATA);

	size_t i = 0;
	while (i < 512) OLED_SPI(buff[i++]);
	SPI_send();
}

void OLED_kb_inv(byte b, byte i, byte sel_s, byte sel_e)
{
	if (i >= sel_s && i <= sel_e) {
		OLED_SPI(~b);
	} else {
		OLED_SPI(b);
	}
}

void OLED_keyboard_line(byte *str, byte sp, byte sel_s, byte sel_e, byte offset)
{
	byte i = 0;
	byte j;
	sel_s += offset;
	sel_e += offset;
	while (i < offset) OLED_kb_inv(0x00, i++, sel_s, sel_e);
	while (*str && i < (128 - 4 - sp)) {
		for (j = 0; j < 5; j++) {
		  OLED_kb_inv(OLED_characters2[(*str - 32) * 5 + j], i++, sel_s, sel_e);
		}
		for (j = 0; j < sp; j++) OLED_kb_inv(0x00, i++, sel_s, sel_e);
		str++;
	}
	while (i < 128) OLED_kb_inv(0x00, i++, sel_s, sel_e);	
	SPI_send();
	
}

void	OLED_putstr(byte *str, byte options, byte offset)
{
	uint8_t		tmp;
	uint8_t		j;
	uint8_t		i;
	byte		merged;
	byte		icon_bytes = 0;
	
	SPI_slave_select(SPI_OLED);

	if (OLED_page == 0 && (wifi_async_status != WIFI_IDLE ||
			!FAT32_working || !SD_working))
		icon_bytes = OLED_wifi_icon;
	
	
	if (offset > 128 - icon_bytes) offset = 128 - icon_bytes;
	if (options & OLED_FONT_DOUBLE)
	{
		options ^= OLED_FONT_DOUBLE;
		options |= OLED_FONT_IS_HALF;
		OLED_putstr(str, options | OLED_FONT_TOP, offset);
		OLED_putstr(str, options, offset);
		return;
	}
	
	j = 0;
	shiftreg_set(PIN_OLED_DC, DATA);
	for(i = 0; i < offset; i++)
		OLED_filler(i, options);
	
	
	byte chars_allowed;
	if (icon_bytes) {
		chars_allowed = (128 - icon_bytes - offset) / 6;
	} else {
		chars_allowed = (128 - offset) / 6;
	}
	
	while (str[j] && j < chars_allowed)
    {
		tmp = (str[j] - 32);
		if (j == chars_allowed - 1) tmp = '\xB0' - 32; // Ellipsis
		for(i = 0; i < 5; i++) {
			merged = OLED_extend_char(OLED_characters2[tmp * 5 + i], options);
			if (options & OLED_FONT_TRANSPARENT)
				merged |= FAT32_BUFFER[128 * (OLED_page % 4) + i + offset + (j * 6)];
			if (options & OLED_FONT_INVERTED)
				merged = ~merged;
			OLED_SPI(merged);
		}
		OLED_filler(i + (j * 6) + offset, options);
		j++;
	}

	for(i = 0; i < 128 - (j * 6) - offset - icon_bytes; i++) 
		OLED_filler(i + (j * 6) + offset, options);
	for (i = 0; i < icon_bytes; i++) {
		if (wifi_async_status == WIFI_BUSY) {
			OLED_SPI(OLED_wifi[i]);
		} else if (wifi_async_status == WIFI_ERROR) {
			OLED_SPI(OLED_wifi_err[i]);
		} else {
			OLED_SPI(0xFF);
		}
	}

	SPI_send();
	if (OLED_page < 7) OLED_page++;
	else OLED_page = 0;
}

byte OLED_extend_char(byte b, byte mask)
{
	byte pos = 0;
	byte out = 0x00;
	
	if (!(mask & OLED_FONT_IS_HALF))
		return (b);
	if (mask & OLED_FONT_TOP)
		mask = 0b00001000;
	else
		mask = 0b10000000;
	
	while (pos < 4)
	{
		if (mask & b)
		{
			out <<= 1;
			out += 0x01;
			out <<= 1;
			out += 0x01;
		}
		else
		{
			out <<= 1;
			out += 0x00;
			out <<= 1;
			out += 0x00;
		}
		mask >>= 1;
		pos++;
	}
	return (out);
}

void	OLED_wake(void)
{
	SPI_slave_select(SPI_OLED);
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0xAF);
	SPI_send();
}

void	OLED_sleep(void)
{
	SPI_slave_select(SPI_OLED);
	shiftreg_set(PIN_OLED_DC, COMMAND);
	OLED_SPI(0xAE);
	SPI_send();
}
