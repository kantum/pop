#ifndef SCREEN_H
#define	SCREEN_H

#define COMMAND LOW
#define DATA	HIGH
#define OLED_SPI(x) SPI_queue_byte(x, 1)

#define	WHITE		0xFF
#define	BLACK		0x0
#define	CONTRAST	200

#define OLED_FONT_NORMAL        0b00000000
#define OLED_FONT_DOUBLE        0b00000001
#define OLED_FONT_IS_HALF       0b00000010
#define OLED_FONT_TOP           0b00000100
#define OLED_FONT_INVERTED      0b00001000
#define OLED_FONT_TRANSPARENT   0b00010000

//0 > Font Regular/Double 
//0 > Is Halved
//0 > Halved Bottom Top
//0 > Normal/Inverted
//0 > Opaque/Transparent Background
//0 > 
//0 > 
//0 >

void	OLED_refresh(void);
void	OLED_fill(byte color);
void	OLED_wake(void);
void	OLED_run(void);
void	OLED_run(void);
void	OLED_putstr(byte *str, byte font, byte offset);
byte	OLED_extend_char(byte b, byte lvl);
void	OLED_set_contrast(byte contrast);

#define OLED_wifi_icon      14    
static const unsigned char OLED_wifi[] = {
    0x06, 0x02, 0x1B, 0x0D, 0x25, 0x35, 0x55, 0x35, 0x25, 0x0D, 0x1B, 0x02, 0x06, 0x00
};
static const unsigned char OLED_wifi_err[] = {
    0x06, 0x02, 0x1B, 0x0D, 0x05, 0x00, 0x5F, 0x00, 0x05, 0x0D, 0x1B, 0x02, 0x06, 0x00
};

static const unsigned char OLED_img1[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x1c, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static const unsigned char OLED_characters1[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,	 // 	(Space)
	0x00, 0x00, 0x5F, 0x00, 0x00,	 // 	!
	0x00, 0x07, 0x00, 0x07, 0x00,	 // 	"
	0x14, 0x7F, 0x14, 0x7F, 0x14,	 // 	#
	0x24, 0x2A, 0x7F, 0x2A, 0x12,	 // 	$
	0x23, 0x13, 0x08, 0x64, 0x62,	 // 	%
	0x36, 0x49, 0x56, 0x20, 0x50,	 // 	&
	0x00, 0x08, 0x07, 0x03, 0x00,	 // 	'
	0x00, 0x1C, 0x22, 0x41, 0x00,	 // 	(
	0x00, 0x41, 0x22, 0x1C, 0x00,	 // 	)
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,	 // 	*
	0x08, 0x08, 0x3E, 0x08, 0x08,	 // 	+
	0x00, 0x00, 0x70, 0x30, 0x00,	 // 	,
	0x08, 0x08, 0x08, 0x08, 0x08,	 // 	-
	0x00, 0x00, 0x60, 0x60, 0x00,	 // 	.
	0x20, 0x10, 0x08, 0x04, 0x02,	 // 	/
	0x3E, 0x51, 0x49, 0x45, 0x3E,	 // 	0
	0x00, 0x42, 0x7F, 0x40, 0x00,	 // 	1
	0x72, 0x49, 0x49, 0x49, 0x46,	 // 	2
	0x21, 0x41, 0x49, 0x4D, 0x33,	 // 	3
	0x18, 0x14, 0x12, 0x7F, 0x10,	 // 	4
	0x27, 0x45, 0x45, 0x45, 0x39,	 // 	5
	0x3C, 0x4A, 0x49, 0x49, 0x31,	 // 	6
	0x41, 0x21, 0x11, 0x09, 0x07,	 // 	7
	0x36, 0x49, 0x49, 0x49, 0x36,	 // 	8
	0x46, 0x49, 0x49, 0x29, 0x1E,	 // 	9
	0x00, 0x00, 0x14, 0x00, 0x00,	 // 	:
	0x00, 0x40, 0x34, 0x00, 0x00,	 // 	;
	0x00, 0x08, 0x14, 0x22, 0x41,	 // 	<
	0x14, 0x14, 0x14, 0x14, 0x14,	 // 	=
	0x00, 0x41, 0x22, 0x14, 0x08,	 // 	>
	0x02, 0x01, 0x59, 0x09, 0x06,	 // 	?
	0x3E, 0x41, 0x5D, 0x59, 0x4E,	 // 	@
	0x7C, 0x12, 0x11, 0x12, 0x7C,	 // 	A
	0x7F, 0x49, 0x49, 0x49, 0x36,	 // 	B
	0x3E, 0x41, 0x41, 0x41, 0x22,	 // 	C
	0x7F, 0x41, 0x41, 0x41, 0x3E,	 // 	D
	0x7F, 0x49, 0x49, 0x49, 0x41,	 // 	E
	0x7F, 0x09, 0x09, 0x09, 0x01,	 // 	F
	0x3E, 0x41, 0x41, 0x51, 0x73,	 // 	G
	0x7F, 0x08, 0x08, 0x08, 0x7F,	 // 	H
	0x00, 0x41, 0x7F, 0x41, 0x00,	 // 	I
	0x20, 0x40, 0x41, 0x3F, 0x01,	 // 	J
	0x7F, 0x08, 0x14, 0x22, 0x41,	 // 	K
	0x7F, 0x40, 0x40, 0x40, 0x40,	 // 	L
	0x7F, 0x02, 0x1C, 0x02, 0x7F,	 // 	M
	0x7F, 0x04, 0x08, 0x10, 0x7F,	 // 	N
	0x3E, 0x41, 0x41, 0x41, 0x3E,	 // 	O
	0x7F, 0x09, 0x09, 0x09, 0x06,	 // 	P
	0x3E, 0x41, 0x51, 0x21, 0x5E,	 // 	Q
	0x7F, 0x09, 0x19, 0x29, 0x46,	 // 	R
	0x26, 0x49, 0x49, 0x49, 0x32,	 // 	S
	0x03, 0x01, 0x7F, 0x01, 0x03,	 // 	T
	0x3F, 0x40, 0x40, 0x40, 0x3F,	 // 	U
	0x1F, 0x20, 0x40, 0x20, 0x1F,	 // 	V
	0x3F, 0x40, 0x38, 0x40, 0x3F,	 // 	W
	0x63, 0x14, 0x08, 0x14, 0x63,	 // 	X
	0x03, 0x04, 0x78, 0x04, 0x03,	 // 	Y
	0x61, 0x59, 0x49, 0x4D, 0x43,	 // 	Z
	0x00, 0x7F, 0x41, 0x41, 0x41,	 // 	[
	0x02, 0x04, 0x08, 0x10, 0x20,	 // 	"\"
	0x00, 0x41, 0x41, 0x41, 0x7F,	 // 	]
	0x04, 0x02, 0x01, 0x02, 0x04,	 // 	^
	0x40, 0x40, 0x40, 0x40, 0x40,	 // 	_
	0x00, 0x03, 0x07, 0x08, 0x00,	 // 	`
	0x20, 0x54, 0x54, 0x38, 0x40,	 // 	a
	0x7F, 0x28, 0x44, 0x44, 0x38,	 // 	b
	0x38, 0x44, 0x44, 0x44, 0x28,	 // 	c
	0x38, 0x44, 0x44, 0x28, 0x7F,	 // 	d
	0x38, 0x54, 0x54, 0x54, 0x18,	 // 	e
	0x00, 0x08, 0x7E, 0x09, 0x02,	 // 	f
	0x0C, 0x52, 0x52, 0x4A, 0x3C,	 // 	g
	0x7F, 0x08, 0x04, 0x04, 0x78,	 // 	h
	0x00, 0x44, 0x7D, 0x40, 0x00,	 // 	i
	0x20, 0x40, 0x40, 0x3D, 0x00,	 // 	j
	0x7F, 0x10, 0x28, 0x44, 0x00,	 // 	k
	0x00, 0x41, 0x7F, 0x40, 0x00,	 // 	l
	0x7C, 0x04, 0x78, 0x04, 0x78,	 // 	m
	0x7C, 0x08, 0x04, 0x04, 0x78,	 // 	n
	0x38, 0x44, 0x44, 0x44, 0x38,	 // 	o
	0x7C, 0x18, 0x24, 0x24, 0x18,	 // 	p
	0x18, 0x24, 0x24, 0x18, 0x7C,	 // 	q
	0x7C, 0x08, 0x04, 0x04, 0x08,	 // 	r
	0x48, 0x54, 0x54, 0x54, 0x24,	 // 	s
	0x04, 0x04, 0x3F, 0x44, 0x24,	 // 	t
	0x3C, 0x40, 0x40, 0x20, 0x7C,	 // 	u
	0x1C, 0x20, 0x40, 0x20, 0x1C,	 // 	v
	0x3C, 0x40, 0x30, 0x40, 0x3C,	 // 	w
	0x44, 0x28, 0x10, 0x28, 0x44,	 // 	x
	0x4C, 0x50, 0x50, 0x50, 0x3C,	 // 	y
	0x44, 0x64, 0x54, 0x4C, 0x44,	 // 	z
	0x00, 0x08, 0x36, 0x41, 0x00,	 // 	{
	0x00, 0x00, 0x77, 0x00, 0x00,	 // 	|
	0x00, 0x41, 0x36, 0x08, 0x00,	 // 	}
			 0x02, 0x01, 0x02, 0x04, 0x02,	 // 	~
};


const unsigned char OLED_characters2OOOOOLD[(255 - 32) * 5] =
{
	0x00, 0x00, 0x00, 0x00, 0x00,	// sp
	0x00, 0x00, 0x2f, 0x00, 0x00,	// !
	0x00, 0x07, 0x00, 0x07, 0x00,	// "
	0x14, 0x7f, 0x14, 0x7f, 0x14,	// #
	0x24, 0x2a, 0x7f, 0x2a, 0x12,	// $
	0x62, 0x64, 0x08, 0x13, 0x23,	// %
	0x36, 0x49, 0x55, 0x22, 0x50,	// &
	0x00, 0x05, 0x03, 0x00, 0x00,	// '
	0x00, 0x1c, 0x22, 0x41, 0x00,	// (
	0x00, 0x41, 0x22, 0x1c, 0x00,	// )
	0x14, 0x08, 0x3E, 0x08, 0x14,	// *
	0x08, 0x08, 0x3E, 0x08, 0x08,	// +
	0x00, 0x00, 0xA0, 0x60, 0x00,	// ,
	0x08, 0x08, 0x08, 0x08, 0x08,	// -
	0x00, 0x60, 0x60, 0x00, 0x00,	// .
	0x20, 0x10, 0x08, 0x04, 0x02,	// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,	// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,	// 1
	0x42, 0x61, 0x51, 0x49, 0x46,	// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,	// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,	// 4
	0x27, 0x45, 0x45, 0x45, 0x39,	// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,	// 6
	0x01, 0x71, 0x09, 0x05, 0x03,	// 7
	0x36, 0x49, 0x49, 0x49, 0x36,	// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,	// 9
	0x00, 0x36, 0x36, 0x00, 0x00,	// :
	0x00, 0x56, 0x36, 0x00, 0x00,	// ;
	0x08, 0x14, 0x22, 0x41, 0x00,	// <
	0x14, 0x14, 0x14, 0x14, 0x14,	// =
	0x00, 0x41, 0x22, 0x14, 0x08,	// >
	0x02, 0x01, 0x51, 0x09, 0x06,	// ?
	0x32, 0x49, 0x59, 0x51, 0x3E,	// @
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A
	0x7F, 0x49, 0x49, 0x49, 0x36,	// B
	0x3E, 0x41, 0x41, 0x41, 0x22,	// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,	// D
	0x7F, 0x49, 0x49, 0x49, 0x41,	// E
	0x7F, 0x09, 0x09, 0x09, 0x01,	// F
	0x3E, 0x41, 0x49, 0x49, 0x7A,	// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,	// H
	0x00, 0x41, 0x7F, 0x41, 0x00,	// I
	0x20, 0x40, 0x41, 0x3F, 0x01,	// J
	0x7F, 0x08, 0x14, 0x22, 0x41,	// K
	0x7F, 0x40, 0x40, 0x40, 0x40,	// L
	0x7F, 0x02, 0x0C, 0x02, 0x7F,	// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,	// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,	// O
	0x7F, 0x09, 0x09, 0x09, 0x06,	// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,	// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,	// R
	0x46, 0x49, 0x49, 0x49, 0x31,	// S
	0x01, 0x01, 0x7F, 0x01, 0x01,	// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,	// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,	// V
	0x3F, 0x40, 0x38, 0x40, 0x3F,	// W
	0x63, 0x14, 0x08, 0x14, 0x63,	// X
	0x07, 0x08, 0x70, 0x08, 0x07,	// Y
	0x61, 0x51, 0x49, 0x45, 0x43,	// Z
	0x00, 0x7F, 0x41, 0x41, 0x00,	// [ 91
	0x02, 0x04 ,0x08, 0x10, 0x20,	// \92
	0x00, 0x41, 0x41, 0x7F, 0x00,	// ]
	0x04, 0x02, 0x01, 0x02, 0x04,	// ^
	0x40, 0x40, 0x40, 0x40, 0x40,	// _
	0x00, 0x01, 0x02, 0x04, 0x00,	// '
	0x20, 0x54, 0x54, 0x54, 0x78,	// a
	0x7F, 0x48, 0x44, 0x44, 0x38,	// b
	0x38, 0x44, 0x44, 0x44, 0x20,	// c
	0x38, 0x44, 0x44, 0x48, 0x7F,	// d
	0x38, 0x54, 0x54, 0x54, 0x18,	// e
	0x08, 0x7E, 0x09, 0x01, 0x02,	// f
	0x18, 0xA4, 0xA4, 0xA4, 0x7C,	// g
	0x7F, 0x08, 0x04, 0x04, 0x78,	// h
	0x00, 0x44, 0x7D, 0x40, 0x00,	// i
	0x40, 0x80, 0x84, 0x7D, 0x00,	// j
	0x7F, 0x10, 0x28, 0x44, 0x00,	// k
	0x00, 0x41, 0x7F, 0x40, 0x00,	// l
	0x7C, 0x04, 0x18, 0x04, 0x78,	// m
	0x7C, 0x08, 0x04, 0x04, 0x78,	// n
	0x38, 0x44, 0x44, 0x44, 0x38,	// o
	0xFC, 0x24, 0x24, 0x24, 0x18,	// p
	0x18, 0x24, 0x24, 0x18, 0xFC,	// q
	0x7C, 0x08, 0x04, 0x04, 0x08,	// r
	0x48, 0x54, 0x54, 0x54, 0x20,	// s
	0x04, 0x3F, 0x44, 0x40, 0x20,	// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,	// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,	// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,	// w
	0x44, 0x28, 0x10, 0x28, 0x44,	// x
	0x1C, 0xA0, 0xA0, 0xA0, 0x7C,	// y
	0x44, 0x64, 0x54, 0x4C, 0x44,	// z
	0x00, 0x08, 0x36, 0x41, 0x00, 	// {
    0x00, 0x00, 0x7F, 0x00, 0x00,   // |
    0x00, 0x41, 0x36, 0x08, 0x00,   // }
    0x10, 0x08, 0x18, 0x10, 0x08,   // ~
    0x7F, 0x41, 0x41, 0x41, 0x7F,   // DEL 
    0x3E, 0x41, 0x41, 0x41, 0x22,	// C (�)
    0x3C, 0x40, 0x40, 0x20, 0x7C,	// u (�)
	0x38, 0x54, 0x54, 0x54, 0x18,	// e (�)
	0x20, 0x54, 0x54, 0x54, 0x78,	// a (�)
	0x20, 0x54, 0x54, 0x54, 0x78,	// a (�)
	0x20, 0x54, 0x54, 0x54, 0x78,	// a (�)
	0x20, 0x54, 0x54, 0x54, 0x78,	// a (�)
	0x38, 0x44, 0x44, 0x44, 0x20,	// c (�)
	0x38, 0x54, 0x54, 0x54, 0x18,	// e (�)
	0x38, 0x54, 0x54, 0x54, 0x18,	// e (�)
	0x38, 0x54, 0x54, 0x54, 0x18,	// e (�)
	0x00, 0x44, 0x7D, 0x40, 0x00,	// i (�)
	0x00, 0x44, 0x7D, 0x40, 0x00,	// i (�)             [142/0x8C]
	0x00, 0x44, 0x7D, 0x40, 0x00,	// i (�)             [143/0x8D]
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A (�)             [144/0x8E]
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A (�)             [145/0x8F]
	0x7F, 0x49, 0x49, 0x49, 0x41,	// E (�)             [146/0x90]
    0x24, 0x52, 0x3C, 0x4A, 0x44,   // �                 [147/0x91]
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //   (�) (MISSING!)  [148/0x92]
	0x38, 0x44, 0x44, 0x44, 0x38,	// o (�)             [149/0x93]
	0x38, 0x44, 0x44, 0x44, 0x38,	// o (�)             [150/0x94]
	0x38, 0x44, 0x44, 0x44, 0x38,	// o (�)             [151/0x95]
	0x3C, 0x40, 0x40, 0x20, 0x7C,	// u (�)             [152/0x96]
	0x3C, 0x40, 0x40, 0x20, 0x7C,	// u (�)             [153/0x97]
	0x1C, 0xA0, 0xA0, 0xA0, 0x7C,	// y (�)             [154/0x98]
	0x3E, 0x41, 0x41, 0x41, 0x3E,	// O (�)             [153/0x99]
	0x3F, 0x40, 0x40, 0x40, 0x3F,	// U (�)             [154/0x9A]
	0x38, 0x44, 0x44, 0x44, 0x20,	// c (�) (NOT DONE)  [155/0x9B]
	0x48, 0x7E, 0x49, 0x41, 0x42,	// �                 [156/0x9C]
	0x07, 0x08, 0x70, 0x08, 0x07,	// Y (�) (NOT DONE)  [157/0x9D]
    0x7F, 0x41, 0x41, 0x41, 0x7F,   // Pts (NOT DONE)    [158/0x9E]
    0x00, 0x48, 0x3E, 0x09, 0x02,   // ?                 [159/0x9F]
	0x20, 0x54, 0x54, 0x54, 0x78,	// a (�)
	0x00, 0x44, 0x7D, 0x40, 0x00,	// i (�)
	0x38, 0x44, 0x44, 0x44, 0x38,	// o (�)
    0x3C, 0x40, 0x40, 0x20, 0x7C,	// u (�)
	0x7C, 0x08, 0x04, 0x04, 0x78,	// n (�)
	0x7F, 0x04, 0x08, 0x10, 0x7F,	// N (�)
    0x09, 0x15, 0x1E, 0x00, 0x00,   // �                  [166/0xA6] 
    0x06, 0x09, 0x06, 0x00, 0x00,   // �                  [167/0xA7]
	0x30, 0x48, 0x45, 0x40, 0x20,	// �
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (�)
    0x04, 0x04, 0x04, 0x04, 0x1C,   // �
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (1/2)
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (1/4)
	0x00, 0x00, 0x7A, 0x00, 0x00,	// �                  [173/0xAD]
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (<<) 
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (>>) 
    0x40, 0x00, 0x40, 0x00, 0x40, 	// ...                [176/0xB0]
    0x63, 0x41, 0x00, 0x41, 0x63, 	// Selector Char      [177/0xB1]
    0x00, 0x7F, 0x00, 0x00, 0x00, 	// Caret              [178/0xB2]
    0x60, 0x40, 0x40, 0x40, 0x60, 	// Space              [179/0xB3]
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    ([]) 
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A (�)
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A (�)
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// A (�)
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    (�)
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    ([]) 
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    ([]) 
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    ([]) 
    0x7F, 0x41, 0x41, 0x41, 0x7F,   //    ([]) 

    
    
    
};

const unsigned char OLED_characters2[(255 - 31) * 5] =
{
	0x00, 0x00, 0x00, 0x00, 0x00,	//  32 \u0020 space
	0x00, 0x06, 0x5F, 0x06, 0x00,	//  33 \u0021 !
	0x07, 0x03, 0x00, 0x07, 0x03,	//  34 \u0022 "
	0x24, 0x7E, 0x24, 0x7E, 0x24,	//  35 \u0023 #
	0x24, 0x2A, 0x6B, 0x12, 0x00,	//  36 \u0024 $
	0x63, 0x13, 0x08, 0x64, 0x63,	//  37 \u0025 %
	0x36, 0x49, 0x56, 0x20, 0x50,	//  38 \u0026 &
	0x00, 0x07, 0x03, 0x00, 0x00,	//  39 \u0027 '
	0x00, 0x3E, 0x41, 0x00, 0x00,	//  40 \u0028 (
	0x00, 0x41, 0x3E, 0x00, 0x00,	//  41 \u0029 )
	0x08, 0x3E, 0x1C, 0x3E, 0x08,	//  42 \u002a *
	0x08, 0x08, 0x3E, 0x08, 0x08,	//  43 \u002b +
	0x00, 0xE0, 0x60, 0x00, 0x00,	//  44 \u002c ,
	0x08, 0x08, 0x08, 0x08, 0x08,	//  45 \u002d -
	0x00, 0x60, 0x60, 0x00, 0x00,	//  46 \u002e .
	0x20, 0x10, 0x08, 0x04, 0x02,	//  47 \u002f /
	0x3E, 0x51, 0x49, 0x45, 0x3E,	//  48 \u0030 0
	0x00, 0x42, 0x7F, 0x40, 0x00,	//  49 \u0031 1
	0x62, 0x51, 0x49, 0x49, 0x46,	//  50 \u0032 2
	0x22, 0x49, 0x49, 0x49, 0x36,	//  51 \u0033 3
	0x18, 0x14, 0x12, 0x7F, 0x10,	//  52 \u0034 4
	0x2F, 0x49, 0x49, 0x49, 0x31,	//  53 \u0035 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,	//  54 \u0036 6
	0x01, 0x71, 0x09, 0x05, 0x03,	//  55 \u0037 7
	0x36, 0x49, 0x49, 0x49, 0x36,	//  56 \u0038 8
	0x06, 0x49, 0x49, 0x29, 0x1E,	//  57 \u0039 9
	0x00, 0x36, 0x36, 0x00, 0x00,	//  58 \u003a :
	0x00, 0xEC, 0x6C, 0x00, 0x00,	//  59 \u003b ;
	0x08, 0x14, 0x22, 0x41, 0x00,	//  60 \u003c <
	0x24, 0x24, 0x24, 0x24, 0x24,	//  61 \u003d =
	0x00, 0x41, 0x22, 0x14, 0x08,	//  62 \u003e >
	0x02, 0x01, 0x59, 0x09, 0x06,	//  63 \u003f ?
	0x3E, 0x41, 0x5D, 0x55, 0x1E,	//  64 \u0040 @
	0x7E, 0x11, 0x11, 0x11, 0x7E,	//  65 \u0041 A
	0x7F, 0x49, 0x49, 0x49, 0x36,	//  66 \u0042 B
	0x3E, 0x41, 0x41, 0x41, 0x22,	//  67 \u0043 C
	0x7F, 0x41, 0x41, 0x41, 0x3E,	//  68 \u0044 D
	0x7F, 0x49, 0x49, 0x49, 0x41,	//  69 \u0045 E
	0x7F, 0x09, 0x09, 0x09, 0x01,	//  70 \u0046 F
	0x3E, 0x41, 0x49, 0x49, 0x7A,	//  71 \u0047 G
	0x7F, 0x08, 0x08, 0x08, 0x7F,	//  72 \u0048 H
	0x00, 0x41, 0x7F, 0x41, 0x00,	//  73 \u0049 I
	0x30, 0x40, 0x40, 0x40, 0x3F,	//  74 \u004a J
	0x7F, 0x08, 0x14, 0x22, 0x41,	//  75 \u004b K
	0x7F, 0x40, 0x40, 0x40, 0x40,	//  76 \u004c L
	0x7F, 0x02, 0x04, 0x02, 0x7F,	//  77 \u004d M
	0x7F, 0x02, 0x04, 0x08, 0x7F,	//  78 \u004e N
	0x3E, 0x41, 0x41, 0x41, 0x3E,	//  79 \u004f O
	0x7F, 0x09, 0x09, 0x09, 0x06,	//  80 \u0050 P
	0x3E, 0x41, 0x51, 0x21, 0x5E,	//  81 \u0051 Q
	0x7F, 0x09, 0x09, 0x19, 0x66,	//  82 \u0052 R
	0x26, 0x49, 0x49, 0x49, 0x32,	//  83 \u0053 S
	0x01, 0x01, 0x7F, 0x01, 0x01,	//  84 \u0054 T
	0x3F, 0x40, 0x40, 0x40, 0x3F,	//  85 \u0055 U
	0x1F, 0x20, 0x40, 0x20, 0x1F,	//  86 \u0056 V
	0x3F, 0x40, 0x3C, 0x40, 0x3F,	//  87 \u0057 W
	0x63, 0x14, 0x08, 0x14, 0x63,	//  88 \u0058 X
	0x07, 0x08, 0x70, 0x08, 0x07,	//  89 \u0059 Y
	0x71, 0x49, 0x45, 0x43, 0x00,	//  90 \u005a Z
	0x00, 0x7F, 0x41, 0x41, 0x00,	//  91 \u005b [
	0x02, 0x04, 0x08, 0x10, 0x20,	//  92 \u005c slash
	0x00, 0x41, 0x41, 0x7F, 0x00,	//  93 \u005d ]
	0x04, 0x02, 0x01, 0x02, 0x04,	//  94 \u005e ^
	0x80, 0x80, 0x80, 0x80, 0x80,	//  95 \u005f _
	0x00, 0x03, 0x07, 0x00, 0x00,	//  96 \u0060 `
	0x20, 0x54, 0x54, 0x54, 0x78,	//  97 \u0061 a
	0x7F, 0x44, 0x44, 0x44, 0x38,	//  98 \u0062 b
	0x38, 0x44, 0x44, 0x44, 0x28,	//  99 \u0063 c
	0x38, 0x44, 0x44, 0x44, 0x7F,	// 100 \u0064 d
	0x38, 0x54, 0x54, 0x54, 0x08,	// 101 \u0065 e
	0x08, 0x7E, 0x09, 0x09, 0x00,	// 102 \u0066 f
	0x18, 0xA4, 0xA4, 0xA4, 0x7C,	// 103 \u0067 g
	0x7F, 0x04, 0x04, 0x78, 0x00,	// 104 \u0068 h
	0x00, 0x00, 0x7D, 0x40, 0x00,	// 105 \u0069 i
	0x40, 0x80, 0x84, 0x7D, 0x00,	// 106 \u006a j
	0x7F, 0x10, 0x28, 0x44, 0x00,	// 107 \u006b k
	0x00, 0x00, 0x7F, 0x40, 0x00,	// 108 \u006c l
	0x7C, 0x04, 0x18, 0x04, 0x78,	// 109 \u006d m
	0x7C, 0x04, 0x04, 0x78, 0x00,	// 110 \u006e n
	0x38, 0x44, 0x44, 0x44, 0x38,	// 111 \u006f o
	0xFC, 0x44, 0x44, 0x44, 0x38,	// 112 \u0070 p
	0x38, 0x44, 0x44, 0x44, 0xFC,	// 113 \u0071 q
	0x44, 0x78, 0x44, 0x04, 0x08,	// 114 \u0072 r
	0x08, 0x54, 0x54, 0x54, 0x20,	// 115 \u0073 s
	0x04, 0x3E, 0x44, 0x24, 0x00,	// 116 \u0074 t
	0x3C, 0x40, 0x20, 0x7C, 0x00,	// 117 \u0075 u
	0x1C, 0x20, 0x40, 0x20, 0x1C,	// 118 \u0076 v
	0x3C, 0x60, 0x30, 0x60, 0x3C,	// 119 \u0077 w
	0x6C, 0x10, 0x10, 0x6C, 0x00,	// 120 \u0078 x
	0x9C, 0xA0, 0x60, 0x3C, 0x00,	// 121 \u0079 y
	0x64, 0x54, 0x54, 0x4C, 0x00,	// 122 \u007a z
	0x08, 0x3E, 0x41, 0x41, 0x00,	// 123 \u007b {
	0x00, 0x00, 0xFF, 0x00, 0x00,	// 124 \u007c |
	0x00, 0x41, 0x41, 0x3E, 0x08,	// 125 \u007d }
	0x02, 0x01, 0x02, 0x01, 0x00,	// 126 \u007e ~
	0x40, 0x00, 0x40, 0x00, 0x40,   // Ellipsis     //0x80, 0x80, 0x80, 0x80, 0x00,	// 127 \u2581 lower 1/8 block (trim)
	0x63, 0x41, 0x00, 0x41, 0x63,   // Selector     // 0xC0, 0xC0, 0xC0, 0xC0, 0x00,	// 128 \u2582 lower 1/4 block (trim)
	0x00, 0x7F, 0x00, 0x00, 0x00,   // Caret        //0xE0, 0xE0, 0xE0, 0xE0, 0x00,	// 129 \u2583 lower 3/8 block (trim)
	0x60, 0x40, 0x40, 0x40, 0x60,   // Space Visible //0xF0, 0xF0, 0xF0, 0xF0, 0x00,	// 130 \u2584 lower 1/2 block (trim)
	0xF8, 0xF8, 0xF8, 0xF8, 0x00,	// 131 \u2585 lower 5/8 block (trim)
	0xFC, 0xFC, 0xFC, 0xFC, 0x00,	// 132 \u2586 lower 3/4 block (trim)
	0xFE, 0xFE, 0xFE, 0xFE, 0x00,	// 133 \u2587 lower 7/8 block (trim)
	0xFF, 0xFF, 0xFF, 0xFF, 0x00,	// 134 \u2588 full block (vert trim)
	0x00, 0x00, 0x00, 0x00, 0x00,	// 135 \u258f left 1/6 block (trim)
	0x3C, 0x00, 0x00, 0x00, 0x00,	// 136 \u258e left 1/3 block (trim)
	0x3C, 0x3C, 0x00, 0x00, 0x00,	// 137 \u258c left 1/2 block (trim)
	0x3C, 0x3C, 0x3C, 0x00, 0x00,	// 138 \u258b left 2/3 block (trim)
	0x3C, 0x3C, 0x3C, 0x3C, 0x00,	// 139 \u258a left 5/6 block (trim)
	0x3C, 0x3C, 0x3C, 0x3C, 0x3C,	// 140 \u2588 full block (horiz trim)
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 141 \u2588 really full block
	0x22, 0x55, 0x59, 0x30, 0x00,	// 142 \u03b4 delta
	0x1C, 0x2A, 0x2A, 0x2A, 0x00,	// 143 \u03b5 epsilon
	0x02, 0x7E, 0x02, 0x7E, 0x02,	// 144 \u03c0 pi
	0x18, 0x24, 0x24, 0x1C, 0x04,	// 145 \u03c3 sigma
	0x08, 0x04, 0x78, 0x04, 0x00,	// 146 \u03c4 tau
	0x18, 0x24, 0x7E, 0x24, 0x18,	// 147 \u03c6 phi
	0x18, 0x24, 0x18, 0x24, 0x18,	// 148 \u221e infinity
	0x7F, 0x01, 0x01, 0x03, 0x00,	// 149 \u0393 Gamma
	0x3E, 0x49, 0x49, 0x3E, 0x00,	// 150 \u0398 Theta
	0x08, 0x55, 0x77, 0x55, 0x08,	// 151 \u03a6 Phi
	0x4C, 0x72, 0x02, 0x72, 0x4C,	// 152 \u03a9 Omega
	0x8C, 0x8C, 0x94, 0x94, 0xA4,	// 153        left half of mail icon
	0x94, 0x94, 0x8C, 0x8C, 0xFC,	// 154        right half of mail icon
	0x08, 0x1C, 0x2A, 0x08, 0x08,	// 155 \u2190 left arrow
	0x04, 0x02, 0x7F, 0x02, 0x04,	// 156 \u2191 up arrow
	0x08, 0x08, 0x2A, 0x1C, 0x08,	// 157 \u2192 right arrow
	0x10, 0x20, 0x7F, 0x20, 0x10,	// 158 \u2193 down arrow
	0x1C, 0x2A, 0x2A, 0x1C, 0x08,	// 159 \u2194 left right arrrow
	0x00, 0x00, 0x00, 0x00, 0x00,	// 160
	0x00, 0x30, 0x7D, 0x30, 0x00,	// 161 \u00a1 � inverted exclamation mark
	0x18, 0x24, 0x7E, 0x24, 0x00,	// 162 \u00a2 � cent
	0x48, 0x3E, 0x49, 0x49, 0x62,	// 163 \u00a3 � pound
	0x38, 0x54, 0x54, 0x44, 0x28,	// 164 \u20ac � euro
	0x29, 0x2A, 0x7C, 0x2A, 0x29,	// 165 \u00a5 � yen
	0x48, 0x55, 0x56, 0x55, 0x24,	// 166 \u0160 � capital S with caron
	0x22, 0x4D, 0x55, 0x59, 0x22,	// 167 \u00a7 � section
	0x08, 0x55, 0x56, 0x55, 0x20,	// 168 \u0161 � small s with caron
	0x38, 0x7C, 0x6C, 0x44, 0x38,	// 169 \u00a9 � copyright
	0x08, 0x55, 0x55, 0x55, 0x5E,	// 170 \u00aa � feminine ordinal
	0x08, 0x14, 0x00, 0x08, 0x14,	// 171 \u00ab � left double angle
	0x04, 0x04, 0x04, 0x04, 0x1C,	// 172 \u00ac � not
	0x08, 0x08, 0x08, 0x08, 0x08,	// 173 \u00ad � hyphen
	0x38, 0x7C, 0x5C, 0x74, 0x38,	// 174 \u00ae � registered
	0x01, 0x01, 0x01, 0x01, 0x01,	// 175 \u00af � macron
	0x06, 0x09, 0x09, 0x09, 0x06,	// 176 \u00b0 � degree
	0x24, 0x24, 0x3F, 0x24, 0x24,	// 177 \u00b1 � plus-minus
	0x09, 0x0D, 0x0A, 0x00, 0x00,	// 178 \u00b2 � superscript 2
	0x15, 0x15, 0x0A, 0x00, 0x00,	// 179 \u00b3 � superscript 3
	0x65, 0x56, 0x4E, 0x45, 0x00,	// 180 \u017d � Z caron
	0xFC, 0x20, 0x20, 0x1C, 0x00,	// 181 \u00b5 � micro
	0x06, 0x09, 0x7F, 0x01, 0x7F,	// 182 \u00b6 � paragraph
	0x00, 0x18, 0x18, 0x00, 0x00,	// 183 \u00b7 � middle dot
	0x65, 0x56, 0x56, 0x4D, 0x00,	// 184 \u017e � z caron
	0x12, 0x1F, 0x10, 0x00, 0x00,	// 185 \u00b9 � superscript 1
	0x4E, 0x51, 0x51, 0x4E, 0x00,	// 186 \u00ba � masculine ordinal
	0x14, 0x08, 0x00, 0x14, 0x08,	// 187 \u00bb � right double angle
	0x7F, 0x41, 0x7F, 0x49, 0x49,	// 188 \u0152 � OE
	0x7C, 0x44, 0x7C, 0x54, 0x48,	// 189 \u0153 � oe
	0x04, 0x09, 0x70, 0x09, 0x04,	// 190 \u0178 � Y diaeresis
	0x30, 0x48, 0x4D, 0x40, 0x20,	// 191 \u00bf � inverted question mark
	0x70, 0x29, 0x25, 0x2A, 0x70,	// 192 \u00c0 � A grave
	0x70, 0x2A, 0x25, 0x29, 0x70,	// 193 \u00c1 � A acute
	0x70, 0x2A, 0x25, 0x2A, 0x70,	// 194 \u00c2 � A circumflex
	0x72, 0x29, 0x26, 0x29, 0x70,	// 195 \u00c3 � A tilde
	0x70, 0x29, 0x24, 0x29, 0x70,	// 196 \u00c4 � A diaeresis
	0x78, 0x2F, 0x25, 0x2F, 0x78,	// 197 \u00c5 � A ring
	0x7E, 0x09, 0x7F, 0x49, 0x49,	// 198 \u00c6 � AE
	0x1E, 0xA1, 0xE1, 0x21, 0x12,	// 199 \u00c7 � C cedilla
	0x7C, 0x55, 0x55, 0x56, 0x46,	// 200 \u00c8 � E grave
	0x7C, 0x56, 0x56, 0x55, 0x45,	// 201 \u00c9 � E acute
	0x7E, 0x55, 0x55, 0x56, 0x44,	// 202 \u00ca � E circumflex
	0x7C, 0x55, 0x54, 0x54, 0x45,	// 203 \u00cb � E diaeresis
	0x00, 0x45, 0x7D, 0x46, 0x00,	// 204 \u00cc � I grave
	0x00, 0x46, 0x7D, 0x45, 0x00,	// 205 \u00cd � I acute
	0x00, 0x46, 0x7D, 0x46, 0x00,	// 206 \u00ce � I circumflex
	0x00, 0x45, 0x7C, 0x45, 0x00,	// 207 \u00cf � I diaeresis
	0x7F, 0x49, 0x49, 0x41, 0x3E,	// 208 \u00d0 � Eth
	0x7A, 0x11, 0x22, 0x79, 0x00,	// 209 \u00d1 � N tilde
	0x39, 0x45, 0x46, 0x38, 0x00,	// 210 \u00d2 � O grave
	0x38, 0x46, 0x45, 0x39, 0x00,	// 211 \u00d3 � O acute
	0x38, 0x46, 0x45, 0x3A, 0x00,	// 212 \u00d4 � O circumflex
	0x3A, 0x45, 0x46, 0x39, 0x00,	// 213 \u00d5 � O tilde
	0x39, 0x44, 0x44, 0x39, 0x00,	// 214 \u00d6 � O diaeresis
	0x28, 0x10, 0x10, 0x28, 0x00,	// 215 \u00d7 � multiplication
	0x3E, 0x61, 0x5D, 0x43, 0x3E,	// 216 \u00d8 � O slash
	0x3C, 0x41, 0x41, 0x3E, 0x00,	// 217 \u00d9 � U grave
	0x3C, 0x42, 0x41, 0x3D, 0x00,	// 218 \u00da � U acute
	0x38, 0x42, 0x41, 0x3A, 0x00,	// 219 \u00db � U circumflex
	0x3C, 0x41, 0x40, 0x3D, 0x00,	// 220 \u00dc � U diaeresis
	0x04, 0x0A, 0x71, 0x09, 0x04,	// 221 \u00dd � Y acute
	0xFF, 0x44, 0x44, 0x44, 0x38,	// 222 \u00de � Thorn
	0x7E, 0x0A, 0x4A, 0x34, 0x00,	// 223 \u00df � Eszett
	0x20, 0x55, 0x55, 0x56, 0x78,	// 224 \u00e0 � a grave
	0x20, 0x56, 0x55, 0x55, 0x78,	// 225 \u00e1 � a acute
	0x20, 0x56, 0x55, 0x56, 0x78,	// 226 \u00e2 � a circumplex
	0x20, 0x56, 0x55, 0x56, 0x79,	// 227 \u00e3 � a tilde
	0x20, 0x55, 0x54, 0x55, 0x78,	// 228 \u00e4 � a diaeresis
	0x20, 0x57, 0x55, 0x57, 0x78,	// 229 \u00e5 � a ring
	0x34, 0x54, 0x7C, 0x54, 0x58,	// 230 \u00e6 � ae
	0x1C, 0xA2, 0xE2, 0x22, 0x14,	// 231 \u00e7 � c cedilla
	0x38, 0x55, 0x55, 0x56, 0x08,	// 232 \u00e8 � e grave
	0x38, 0x54, 0x56, 0x55, 0x09,	// 233 \u00e9 � e acute
	0x38, 0x56, 0x55, 0x56, 0x08,	// 234 \u00ea � e circumflex
	0x38, 0x55, 0x54, 0x55, 0x08,	// 235 \u00eb � e diaeresis
	0x00, 0x01, 0x7D, 0x42, 0x00,	// 236 \u00ec � i grave
	0x00, 0x02, 0x7D, 0x41, 0x00,	// 237 \u00ed � i acute
	0x00, 0x02, 0x79, 0x42, 0x00,	// 238 \u00ee � i circumflex
	0x00, 0x01, 0x7C, 0x41, 0x00,	// 239 \u00ef � i diaeresis
	0x39, 0x47, 0x45, 0x45, 0x3E,	// 240 \u00f0 � eth
	0x7A, 0x09, 0x0A, 0x71, 0x00,	// 241 \u00f1 � n tilde
	0x39, 0x45, 0x46, 0x38, 0x00,	// 242 \u00f2 � o grave
	0x38, 0x46, 0x45, 0x39, 0x00,	// 243 \u00f3 � o acute
	0x38, 0x46, 0x45, 0x3A, 0x00,	// 244 \u00f4 � o circumflex
	0x3A, 0x45, 0x46, 0x39, 0x00,	// 245 \u00f5 � o tilde
	0x38, 0x45, 0x44, 0x39, 0x00,	// 246 \u00f6 � o diaeresis
	0x08, 0x08, 0x2A, 0x08, 0x08,	// 247 \u00f7 � division
	0xB8, 0x64, 0x54, 0x4C, 0x3A,	// 248 \u00f8 � o slash
	0x3D, 0x41, 0x22, 0x7C, 0x00,	// 249 \u00f9 � u grave
	0x3C, 0x42, 0x21, 0x7D, 0x00,	// 250 \u00fa � u acute
	0x38, 0x42, 0x21, 0x7A, 0x00,	// 251 \u00fb � u circumflex
	0x3C, 0x41, 0x20, 0x7D, 0x00,	// 252 \u00fc � u diaeresis
	0x9C, 0xA2, 0x61, 0x3D, 0x00,	// 253 \u00fd � y acute
	0xFF, 0x48, 0x48, 0x48, 0x30,	// 254 \u00fe � thorn
	0x9C, 0xA1, 0x60, 0x3d, 0x00  	// 255 \u00ff � y diaeresis   
};

static char OLED_buffer[128 * 32 / 8] = { //Perpopulated with the Microchip logo
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC,
	0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0x7F, 0x7F, 0xFF, 0xC7, 0x81, 0x00, 0x00, 0x01, 0x07, 0x0F,
	0x3F, 0xFF, 0xFF, 0xC7, 0x01, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x3E, 0xFC, 0xF0, 0xC0, 0x80, 0x00,
	0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0xFF, 0xFC, 0xF0, 0x80, 0xE0, 0xF8, 0xFF, 0x7F, 0xFF,
	0xFF, 0xFE, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0xF0, 0xF8, 0xFC, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C,
	0x38, 0x00, 0xFC, 0xFC, 0xFC, 0x9C, 0x9C, 0x9C, 0x9C, 0xFC, 0xFC, 0xF8, 0x00, 0xF0, 0xF8, 0xFC,
	0x1C, 0x1C, 0x1C, 0x3C, 0xFC, 0xF8, 0xF0, 0x00, 0xF8, 0xFC, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C,
	0x3C, 0x00, 0xFC, 0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xFC, 0xFC, 0xFC, 0x00, 0xFC, 0xFC, 0xF8,
	0x00, 0xFC, 0xFC, 0xFC, 0x1C, 0x1C, 0x1C, 0x1C, 0xFC, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x80, 0xC1, 0xF7, 0xFF, 0xFE, 0xF8, 0xF0, 0xC0, 0x80,
	0x00, 0x00, 0x81, 0xC7, 0xFF, 0xFE, 0xF8, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x06,
	0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x1F,
	0x3F, 0x3F, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x0F, 0x1F, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C,
	0x1C, 0x00, 0x3F, 0x3F, 0x1F, 0x07, 0x07, 0x07, 0x07, 0x3F, 0x3F, 0x1C, 0x00, 0x0F, 0x1F, 0x3F,
	0x3C, 0x3C, 0x3C, 0x3C, 0x3F, 0x1F, 0x0F, 0x00, 0x1F, 0x3F, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C,
	0x3C, 0x00, 0x1F, 0x3F, 0x3F, 0x03, 0x03, 0x03, 0x03, 0x3F, 0x3F, 0x1F, 0x00, 0x3F, 0x3F, 0x1F,
	0x00, 0x3F, 0x3F, 0x1F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F,
	0x3E, 0x3E, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F, 0x0F, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif	/* SCREEN_H */

