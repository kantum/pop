#include "UI.h"
#include <string.h>

int32_t	UI_list_scroll = 0;

bool	UI_needs_repaint = true;
bool	UI_mode = UI_NONE;

char	UI_list[UI_LIST_MAX_SZ][50];
size_t	UI_list_size = 0;

file_t	ui_bck_msg;
bool	ui_bck_msg_ = false;

file_t	ui_bck_img;
bool	ui_bck_img_ = false;

file_t	ui_bck_wifi;
bool	ui_bck_wifi_ = false;


void	UI_init(void)
{
	if (FAT32_fopen(FAT32_ROOT_DIRECTORY, "fra1.dat", &ui_bck_msg))
		ui_bck_msg_ = true;
}

void    UI_set_scroll(int32_t sc) {
	UI_list_scroll = sc;
}

bool	UI_scroll(byte dir)
{
	if (dir == SCROLL_RST) {
		UI_list_scroll = 0;
		return (true);
	}
	if (dir == SCROLL_UP) {
		if (UI_list_scroll >= UI_list_size) return(false); 
		UI_list_scroll++;
	} else if (dir == SCROLL_DOWN) {
		if (UI_list_scroll <= 0) return (false);
		UI_list_scroll--;
	}
	UI_needs_repaint = true;
	return (true);
}

void	UI_repaint(void)
{
	if (!UI_needs_repaint) return;
	UI_needs_repaint = false;
	if (UI_mode == UI_NONE) {
		return;
	} else if (UI_mode == UI_LIST) {
		UI_paint_list();
	}
//	delay_ms(10);
}

void	UI_request_repaint()
{
	UI_needs_repaint = true;
}

byte UI_message(char *msg, byte settings, size_t timeout)
{
	UI_mode = UI_MSG;
	UI_paint_msg(msg);
	delay_ms(UI_PRESS_DELAY);
	if (settings & UI_IGNORE_EVENTS) {
		delay_ms(timeout);
		return (UI_EXPIRED_TMOUT);
	}
	
	byte evnt;
	while (true) {
		if (timeout == 0) // If timeout is 0 keep looking for an event indefinitely 
			evnt = wheel_get_event();
		else
			evnt = wheel_get_event_timeout(timeout);
		if (evnt == WHEEL_NONE && timeout) break;
		if (evnt == WHEEL_PRESS) { return (UI_OK); }
		if (settings & UI_DISSMISSED_BY_ALL_EVENTS) { return (UI_OK); }
	}
}

byte UI_prompt(char *msg)
{
	byte selected = UI_OK;
	UI_mode = UI_MSG;
	UI_paint_prompt(msg, selected);
	delay_ms(UI_PRESS_DELAY);
	
	byte evnt;
	while (true) {
		UI_paint_prompt(msg, selected);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS) { return (selected); }
		if (evnt == WHEEL_TURN_LEFT) { selected = UI_CANCEL; }
		if (evnt == WHEEL_TURN_RIGHT) { selected = UI_OK; }
	}
	return (UI_EXPIRED_TMOUT);
}

int32_t UI_number(char *msg, int32_t val, int32_t min, int32_t max, int32_t step, void (*callback)(byte))
{
	UI_mode = UI_MSG;
	UI_paint_number(msg, val);
	delay_ms(UI_PRESS_DELAY);
	
	byte evnt;
	while (true) {
		UI_paint_number(msg, val);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS) { return (val); }
		if (evnt == WHEEL_TURN_LEFT) { val -= step; }
		if (evnt == WHEEL_TURN_RIGHT) { val += step; }
		if (val < min) val = min;
		if (val > max) val = max;
		if (callback) {
			callback(val);
		}
	}
	return (UI_EXPIRED_TMOUT);
}

void UI_distance_test(void)
{
	size_t val;
	UI_mode = UI_MSG;
	UI_paint_number("Non", val);
	delay_ms(UI_PRESS_DELAY);
	
	byte evnt;
	while (true) {
		val = check_photo();
		if (val > settings_distance)
			UI_paint_number("Activated", settings_distance);
		else
			UI_paint_number("Non", val);
		evnt = wheel_get_event_timeout(100);
		if (evnt == WHEEL_PRESS) { return; }
	}
}

uint16_t UI_distance(void)
{
	size_t val = check_photo();
	UI_mode = UI_MSG;
	UI_paint_number("Distance", val);
	delay_ms(UI_PRESS_DELAY);
	
	byte evnt;
	while (true) {
		val = check_photo();
		UI_paint_number("Distance", val);
		evnt = wheel_get_event_timeout(100);
		if (evnt == WHEEL_PRESS) { return (val); }
	}
	return (UI_EXPIRED_TMOUT);
}

void UI_paint_number(char *str, int32_t val)
{
	static byte str_val[10];
	ltoa(str_val, val, 10);
	UI_list_clear();
	UI_list_set(0, str_val);
	UI_list_set(1, str);
	UI_list_start();
	UI_repaint();
}

void UI_paint_msg(char *str)
{
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_msg_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	FAT32_fseek(&ui_bck_msg, 0);
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	UI_putstr_aligned(str, options | OLED_FONT_DOUBLE, 0, UI_CENTER);
	
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
//	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
}

void UI_paint_img(char *path)
{
	ui_bck_img_ = false;
	if (FAT32_fopen(FAT32_ROOT_DIRECTORY, path, &ui_bck_img))
		ui_bck_img_ = true;
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_img_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	FAT32_fseek(&ui_bck_img, 0);
	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putstr("", options, 128);
	OLED_putstr("", options, 128);
	OLED_putstr("", options, 128);
	
	if (ui_bck_img_)
		OLED_putstr("", options, 0);
	else 
		UI_putstr_aligned("X", options, 0, UI_CENTER);

	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putstr("", options, 128);
	OLED_putstr("", options, 128);
	OLED_putstr("", options, 128);
	OLED_putstr("", options, 128);

}


void UI_animate_sleepy(void)
{
	size_t len = 4;
	while (len--) {
		UI_paint_img("eye_F.dat");
		UI_paint_img("e_b1_F.dat");
		UI_paint_img("e_b2_F.dat");
		UI_paint_img("e_b3_F.dat");
		UI_paint_img("eye_C.dat");
	}
}

void UI_animate_looking(void)
{
	size_t len = 4;
	while (len--) {
		UI_paint_img("eye_UL.dat");
		delay_ms(100);
		UI_paint_img("eye_C.dat");
		UI_paint_img("e_b3_UL.dat");
		UI_paint_img("eye_C.dat");
	}
}

void UI_paint_prompt(char *str, byte selected)
{
	ui_bck_img_ = false;
	if (selected == UI_OK) {
		if (FAT32_fopen(FAT32_ROOT_DIRECTORY, "eye_DR.dat", &ui_bck_img))
			ui_bck_img_ = true;
	} else {
		if (FAT32_fopen(FAT32_ROOT_DIRECTORY, "eye_DL.dat", &ui_bck_img))
			ui_bck_img_ = true;
	}
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_img_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	FAT32_fseek(&ui_bck_img, 0);
	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);

	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	UI_putstr_aligned(str, options, 0, UI_CENTER);
	OLED_putstr("", options, 0);
	if (selected == UI_OK)
		UI_putstr_aligned(" CANCEL       >OK<", options, 0, UI_CENTER);
	else if (selected == UI_CANCEL)
		UI_putstr_aligned(">CANCEL<       OK ", options, 0, UI_CENTER);
}

size_t UI_selected_item(void)
{
	return (UI_list_scroll);
}

void	UI_list_start(void)
{
	UI_mode = UI_LIST;
	UI_needs_repaint = true;
}

void	UI_list_set(size_t i, char *str)
{
	if (!(i < UI_LIST_MAX_SZ)) return;
	if (i > UI_list_size) UI_list_size = i;
	strcpy(UI_list[i], str);
	UI_needs_repaint = true;
}

void	UI_list_clear(void)
{
	UI_list_size = 0;
	UI_list_scroll = 0;
	UI_needs_repaint = true;
}

void	UI_paint_list(void)
{
	int8_t	 i;
	int8_t	 j;
	uint32_t size = UI_list_size;
	byte options;
	byte offset = 0;
	
	j = UI_list_scroll;
	j -= 3;
	OLED_wake();
	OLED_putstr_init();
	for (i = 0; i < 7; i++)
	{
		options = OLED_FONT_NORMAL;
		offset = 3;
		if (i == 6 || i == 0) offset += 1;
		if (i == 5 || i == 1) offset += 2;
		if (i == 4 || i == 2) offset += 4;
		if (i == 3)			  offset += 10;
		if (i == 3) options |= OLED_FONT_DOUBLE;
		if (i + j > size || i + j < 0)
			OLED_putstr("", options, 0);
		else
			UI_putstr_aligned(UI_list[i + j], options, offset, UI_LEFT);
	}
}
void UI_putstr_aligned(char *str, byte options, byte offset, byte alignment) {
	size_t len = 0;
	if (alignment == UI_CENTER) {
		while (str[len++]);
		if (len * 6 > 128)
			offset = 0;
		else
			offset += ((128 - ((len * 6))) /2);
		offset++;
	}
	OLED_putstr(str, options, offset);
}
