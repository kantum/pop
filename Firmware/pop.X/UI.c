#include "UI.h"
#include <string.h>

uint8_t UI_list_scroll = 0;

bool UI_needs_repaint = true;
bool UI_mode          = UI_NONE;

char   UI_list[UI_LIST_MAX_SZ][50];
size_t UI_list_size = 0;

void UI_scroll(byte dir)
{
	if (dir == SCROLL_RST)
	{
		UI_list_scroll = 4;
		return;
	}
	if (dir == SCROLL_UP)
		UI_list_scroll++;
	else if (dir == SCROLL_DOWN)
		UI_list_scroll--;
	UI_needs_repaint = true;
}

void UI_repaint(void)
{
	if (!UI_needs_repaint)
		return;
	UI_needs_repaint = false;
	if (UI_mode == UI_NONE)
	{
		return;
	}
	else if (UI_mode == UI_LIST)
	{
		UI_paint_list();
	}
	delay_ms(10);
}

void UI_list_start(void)
{
	UI_mode          = UI_LIST;
	UI_needs_repaint = true;
}

void UI_list_set(size_t i, char* str)
{
	if (!(i < UI_LIST_MAX_SZ))
		return;
	if (i > UI_list_size)
		UI_list_size = i;
	strcpy(UI_list[i], str);
}

void UI_list_clear(void)
{
	UI_list_size   = 0;
	UI_list_scroll = 0;
}

void UI_paint_list(void)
{
	int8_t  i;
	int8_t  j;
	uint8_t size = UI_list_size;

	j = UI_list_scroll;
	j -= 3;
	OLED_wake();
	OLED_fill(0x0);
	OLED_putstr_init();
	for (i = 0; i < 7; i++)
	{
		byte font = OLED_FONT_NORMAL;
		if (i == 3)
			font = OLED_FONT_DOUBLE;
		if (i + j > size || i + j < 0)
			OLED_putstr("", font, 1);
		else
			OLED_putstr(UI_list[i + j], font, 5);
	}
}
