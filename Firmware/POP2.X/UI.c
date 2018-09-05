#include "UI.h"
#include "translate.h"
#include <string.h>

int32_t	UI_list_scroll = 0;

bool	UI_needs_repaint = true;
bool	UI_mode = UI_NONE;

char	UI_list[UI_LIST_MAX_SZ][50];

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
	
	ui_bck_img_ = true;
	if (!UI_load_buff(UI_BUFF_1, "eye_DR.dat"))
		ui_bck_img_ = false;
	if (!UI_load_buff(UI_BUFF_2, "eye_DL.dat"))
		ui_bck_img_ = false;
	
	UI_paint_prompt(msg, selected);
	delay_ms(UI_PRESS_DELAY);
	wheel_pending_flush();
    
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
	wheel_pending_flush();
    
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
	wheel_pending_flush();
    
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
	UI_paint_number(tr(TR_DISTANCE), val);
	delay_ms(UI_PRESS_DELAY);
	wheel_pending_flush();
    
	byte evnt;
	while (true) {
		val = check_photo();
		UI_paint_number(tr(TR_DISTANCE), val);
		evnt = wheel_get_event_timeout(100);
		if (evnt == WHEEL_PRESS) { return (val); }
	}
	return (UI_EXPIRED_TMOUT);
}

char kb_str[20];
char	*UI_keyboard(void) {
	byte i = 0;
	while (i < 20) kb_str[i++] = 0;
	strcpy(kb_str, "\x81");

	byte len = 0;

	UI_mode = UI_MSG;
	UI_keyboard_paint(kb_str, 0, 0, UI_KB_REGULAR, 1);
	delay_ms(UI_PRESS_DELAY);
	wheel_pending_flush();

	char col = 0;
	char row = 0;
	char slen = 1;
	char kb = UI_KB_REGULAR;
	byte sl;
	byte evnt;
	while (true) {
		sl = UI_keyboard_paint(kb_str, row, col, kb, slen);
		evnt = wheel_get_event();
		if (evnt == WHEEL_PRESS) {
			if (row == 4 && col == 0) { kb_str[len] = 0x00; return (kb_str); } 
			if (sl == 0xB3) sl = ' ';
			if (row == 2 && col == 11) {
				kb++; if (kb == 0x03) kb = 0;
				continue;
			}
			if (row == 0 && col == 12) { // Backspace
				if (len > 0) {
					kb_str[len--] = 0x00;
					kb_str[len]   = '\x81';
				}
			} else {					 // Normal Letter
				if (len < 18) {
					kb_str[len++]   = sl;
					kb_str[len]	 = '\x81';
					kb_str[len + 1] = 0x00;
				}
			}
		}
		if (evnt == WHEEL_TURN_LEFT)  { col--; }
		if (evnt == WHEEL_TURN_RIGHT) { col++; }
		if (col < 0) {
			if (row) { row--; } else { col = 0; continue; }
			if (row == 0) col = 12;
			if (row == 1) col = 12;
			if (row == 2) col = 11;
			if (row == 3) col = 11;
		}
		if (row == 0) {
			if (col == 13) { col = 0; row++; }
		}
		if (row == 1) { if (col > 12) { col = 0; row++; } }
		if (row == 2) {
//			if (col == 9) { col = 11; }
//			if (col == 10) { col = 8; }
			if (col > 11) { col = 0; row++; }
		}
		if (row == 3) {
			if (col > 11) { col = 0; row++; }
		}
		if (row == 4) {
			if (col > 0) { col = 0; }
		}
		if ((col == 11 && row == 2) ||
			(col == 12 && row == 0)) { slen = 2; } else { slen = 1; }
	}
	
}

byte	UI_keyboard_paint(char str[20], size_t row, size_t col, byte kb_, byte len) {
	byte options = OLED_FONT_NORMAL;
	
	OLED_wake();
	OLED_putstr_init();
//	OLED_putstr("", options, 0);
	OLED_putstr(str, options, 3);
	OLED_putstr("", options, 0);

	char *kb[4];
	if (kb_ == UI_KB_REGULAR) {
		kb[0] = "1234567890-=";
		kb[1] = "qwertyuiop[]\\";
		kb[2] = "asdfghjkl;' ^";
		kb[3] = "zxcvbnm\x82<>/~";
	} else if (kb_ == UI_KB_CAPS) {
		kb[0] = "!@#$%^&*()_+";
		kb[1] = "QWERTYUIOP{}|";
		kb[2] = "ASDFGHJKL:\" ^";
		kb[3] = "ZXCVBNM\x82,.?`";
	} else if (kb_ == UI_KB_SPECIAL) {
		kb[0] = "\xAD\x9D\x9C\x9B\x7F\x7F\x7F\x7F\xA6\xA7\x7F\x7F";
		kb[1] = "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F";
		kb[2] = "\x7F\x7F\x7F\x7F\x91\x7F\x7F\x7F\x7F\x7F\x7F ^";
		kb[3] = "\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x82\x7F\x7F\x7F\x7F";
	}
#define KB_SP	4

	byte sel_s = (col * (5 + KB_SP)) - (KB_SP / 2);
	byte sel_e = sel_s + (5 + KB_SP) * len;
	byte r0of = 2;
	byte r1of = 6;
	byte r2of = 8;
	byte r3of = 12;
	if (row == 0) {
		OLED_keyboard_line(kb[0], KB_SP, sel_s, sel_e, r0of);
	} else { OLED_keyboard_line(kb[0], KB_SP, 1, 0, r0of); }
	
	if (row == 1) {
		OLED_keyboard_line(kb[1], KB_SP, sel_s, sel_e, r1of);
	} else { OLED_keyboard_line(kb[1], KB_SP, 1, 0, r1of); }
	
	if (row == 2) {
		OLED_keyboard_line(kb[2], KB_SP, sel_s, sel_e, r2of);
	} else { OLED_keyboard_line(kb[2], KB_SP, 1, 0, r2of); }
	
	if (row == 3) {
		OLED_keyboard_line(kb[3], KB_SP, sel_s, sel_e, r3of);
	} else { OLED_keyboard_line(kb[3], KB_SP, 1, 0, r3of); }
	OLED_putstr("", options, 0);
	if (row == 4) {
		UI_putstr_aligned(tr(TR_OK_SEL), options, 0, UI_CENTER);
	} else {
		UI_putstr_aligned(tr(TR_OK), options, 0, UI_CENTER);
	}
	if (row < 4)
		return (kb[row][col]);
	else
		return (true);
}

uint64_t	UI_password(char *str, byte len) {
	
	if (len < 3 || len > 5) return (0x00);
	byte digits[6];
	int i = 0;
	while (i < 6) {
		digits[i++] = ' ';
	}
	digits[len] = '-';	// 0xAC == End
	UI_paint_pass(str, digits, 0x00, false);

	UI_mode = UI_MSG;
	delay_ms(UI_PRESS_DELAY);
	wheel_pending_flush();

	int sel = 0x00;
	bool blinking = false;
	bool editing = false;
	bool needs_refresh = true;
	byte evnt;
	while (true) {
		if (needs_refresh) {
			if (!editing) UI_paint_pass(str, digits, sel, blinking);
			if (editing) UI_paint_pass(str, digits, sel + 20, 0x00);
			needs_refresh = false;
		}
		if (!editing && sel != len)
			evnt = wheel_get_event_timeout(200);
		else
			evnt = wheel_get_event();
		if (evnt == WHEEL_NONE) {
			needs_refresh = true;
			blinking ^= 1;
		}
		if (evnt == WHEEL_TURN_LEFT) {
			needs_refresh = true;
			blinking = true;
			if (!editing) sel--;
			if (editing) {
				if (digits[sel] == ' ') {
					digits[sel] = 0;
				} else {
					digits[sel]--;
				}
			}
		}
		if (evnt == WHEEL_TURN_RIGHT) {
			needs_refresh = true;
			blinking = true;
			if (!editing) sel++;
			if (editing) {
				if (digits[sel] == ' ') {
					digits[sel] = 9;
				} else {
					digits[sel]++;
				}
			}
		}
		if (evnt == WHEEL_PRESS) {
			if (sel == len) { break; }
			blinking = true;
			needs_refresh = true;
			if (editing == false && digits[sel] == ' ') digits[sel] = 0x00;
			editing ^= 1;
		}
		if (digits[sel] == 0xFF) digits[sel] = 9;
		if (digits[sel] == 10) digits[sel] = 0;
		if (sel < 0)   sel = 0;
		if (sel > len) sel = len;
	}
	
	size_t pass = 0x00;
	i = 0;
	while (i < len) {
		pass *= 10;
		if (digits[i] >= 0 && digits[i] <= 9)
			pass += digits[i];
		i++;
	}
	return (pass);
}

void UI_paint_pass(char *str, char *digits, byte selected, bool blinking)
{
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_msg_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	FAT32_fseek(&ui_bck_msg, 0);
	
	char str_pass[20];
	
	int i = 0;
	int j = 0;
	bool editing = false;
	if (selected >= 20) {
		selected -= 20;
		editing = true;
	}
	while (i < 6) {
		if (digits[i] == '-') {
			break;
		} else if (digits[i] == ' ') {
			if (blinking && selected == i) {
				str_pass[j++] = '\x80';
			} else {
				str_pass[j++] = '_';
			}
		} else if (digits[i] >= 0 && digits[i] <= 9) {
			if (editing) {
				if (selected == i) str_pass[j++] = digits[i] + '0';
				else str_pass[j++] = '*';
			} else {
				if (blinking && selected == i) str_pass[j++] = '\x80';
				else if (selected == i) str_pass[j++] = digits[i] + '0'; //'*';
				else str_pass[j++] = '*';
			}
		} else {
			str_pass[j++] = '?';
		}
		str_pass[j++] = ' ';
		i++;
	}
	str_pass[j - 1] = 0x00;
	
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	OLED_putstr(str, options, 0);
	OLED_putstr("", options, 0);
	UI_putstr_aligned(str_pass, options | OLED_FONT_IS_HALF | OLED_FONT_TOP, 0, UI_CENTER);
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	
	UI_putstr_aligned(str_pass, options | OLED_FONT_IS_HALF, 0, UI_CENTER);	
	OLED_putstr("", options, 0);
	if (selected == i) {
		UI_putstr_aligned(tr(TR_OK_SEL), options, 0, UI_CENTER);
	} else {
		UI_putstr_aligned(tr(TR_OK), options, 0, UI_CENTER);
	}
	OLED_putstr("", options, 0);
}


void UI_paint_number(char *str, int32_t val)
{
	static byte str_val[10];
	ltoa(str_val, val, 10);
	
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_msg_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	if (ui_bck_msg_) FAT32_fseek(&ui_bck_msg, 0);
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr(str, options, 0);
	UI_putstr_aligned(str_val, options | OLED_FONT_IS_HALF | OLED_FONT_TOP, 0, UI_CENTER);
	
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	UI_putstr_aligned(str_val, options | OLED_FONT_IS_HALF, 0, UI_CENTER);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
}

char UI_splitted_msg[UI_MSG_LINE_LEN + 1];
char* UI_split_msg(char **str) {
	size_t i = 0;
	char *end_of_str = 0x00;
	while (i < UI_MSG_LINE_LEN) {
		if ((*str)[i] == ' ') end_of_str = ((*str) + i);
		i++;
	}
	if (end_of_str == 0x00) end_of_str = ((*str) + i);
	i = 0;
	while ((*str != end_of_str)) UI_splitted_msg[i++] = *((*str)++);
	UI_splitted_msg[i] = 0x00;
	return (UI_splitted_msg);
}

void UI_paint_msg(char *str)
{
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_msg_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	if (ui_bck_msg_) FAT32_fseek(&ui_bck_msg, 0);
	if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	if (strlen(str) < UI_MSG_LINE_LEN) {
		UI_putstr_aligned(str, options | OLED_FONT_IS_HALF | OLED_FONT_TOP, 0, UI_CENTER);
		if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
		UI_putstr_aligned(str, options | OLED_FONT_IS_HALF, 0, UI_CENTER);
	} else {
		UI_putstr_aligned(UI_split_msg(&str), options, 0, UI_CENTER);
		if (ui_bck_msg_) FAT32_fgetb(&ui_bck_msg, FAT32_BUFFER);
		UI_putstr_aligned(str, options, 0, UI_CENTER);
	}
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
}

bool UI_load_buff(char *buff, char *path) {
	ui_bck_img_ = false;
	if (!FAT32_fopen(FAT32_ROOT_DIRECTORY, path, &ui_bck_img))
		return (false);
	ui_bck_img_ = true;
	FAT32_fgetb(&ui_bck_img, buff);
	FAT32_fgetb(&ui_bck_img, buff + 512);
	return (true);
}

void UI_paint_buff(char *buff) {
	OLED_wake();
	OLED_putstr_init();
	OLED_putbuff(buff);
	OLED_putbuff(buff + 512);
}

void UI_paint_img(char *path) {
	ui_bck_img_ = false;
	if (FAT32_fopen(FAT32_ROOT_DIRECTORY, path, &ui_bck_img))
		ui_bck_img_ = true;
	OLED_wake();
	OLED_putstr_init();
	FAT32_fseek(&ui_bck_img, 0);
	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putbuff(FAT32_BUFFER);
	if (ui_bck_img_) FAT32_fgetb(&ui_bck_img, FAT32_BUFFER);
	OLED_putbuff(FAT32_BUFFER);
}

void UI_paint_img_old(char *path)
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
	UI_putstr_aligned(path, options, 0, UI_CENTER);
}


void UI_animate_sleepy(void)
{
	size_t len = 4;
	if (!UI_load_buff(UI_BUFF_1, "eye_F.dat") ||
		!UI_load_buff(UI_BUFF_2, "e_b1_F.dat") ||
		!UI_load_buff(UI_BUFF_3, "e_b2_F.dat") ||
		!UI_load_buff(UI_BUFF_4, "e_b3_F.dat") ||
		!UI_load_buff(UI_BUFF_5, "eye_C.dat")) {
		UI_message("Animation Failed\x7F", UI_DISSMISSED_BY_ALL_EVENTS, 0);
		return;
	}
	
#define DLY	50
	while (len--) {
		UI_paint_buff(UI_BUFF_1);
		delay_ms(DLY);
		UI_paint_buff(UI_BUFF_2);
		delay_ms(DLY);
		UI_paint_buff(UI_BUFF_3);
		delay_ms(DLY);
		UI_paint_buff(UI_BUFF_4);
		delay_ms(DLY);
		UI_paint_buff(UI_BUFF_5);
		delay_ms(DLY);
	}
}

void UI_animate_sleepy_old(void)
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
	UI_animate_blink(1);
	delay_ms(200);
	UI_animate_blink(10);
	delay_ms(200);
	UI_animate_blink(25);
	delay_ms(200);
	UI_animate_blink(50);
	UI_paint_img("eye_C.dat");
	delay_ms(5000);
	OLED_fill(0x00);
}

void UI_animate_blink(byte step)
{
	size_t len = 2;
	if (step == 50) len = 1;
	if (!UI_load_buff(UI_BUFF_1, "eye_UL.dat") ||
		!UI_load_buff(UI_BUFF_2, "eye_C.dat") ||
		!UI_load_buff(UI_BUFF_3, "e_b3_UL.dat") ||
		!UI_load_buff(UI_BUFF_4, "eye_C.dat")) {
		UI_message("Animation Failed\x7F", UI_DISSMISSED_BY_ALL_EVENTS, 0);
		return;
	}
		
	while (len--) {
		UI_paint_buff(UI_BUFF_1);
		delay_ms(80 / step);
		UI_paint_buff(UI_BUFF_3);
		delay_ms(20);
		UI_paint_buff(UI_BUFF_4);
		delay_ms(20 * step);
		UI_paint_buff(UI_BUFF_3);
		delay_ms(5 * step);
		UI_paint_buff(UI_BUFF_1);
		delay_ms(200 / step);
		delay_ms(200 / step);
	}
}

void UI_animate_looking_old(void)
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
	char *buff = 0;
	if (selected == UI_OK) {
		buff = UI_BUFF_1;
	} else {
		buff = UI_BUFF_2;
	}
	byte options = OLED_FONT_NORMAL;
	if (ui_bck_img_)
		options |= OLED_FONT_TRANSPARENT;
	OLED_wake();
	OLED_putstr_init();
	
	if (ui_bck_img_) memcpy(FAT32_BUFFER, buff, 512);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);
	OLED_putstr("", options, 0);

	if (ui_bck_img_) memcpy(FAT32_BUFFER, buff + 512, 512);
	OLED_putstr("", options, 0);
	UI_putstr_aligned(str, options, 0, UI_CENTER);
	OLED_putstr("", options, 0);
	if (selected == UI_OK)
		UI_putstr_aligned(tr(TR_CANCEL_OK_SEL), options, 0, UI_CENTER);
	else if (selected == UI_CANCEL)
		UI_putstr_aligned(tr(TR_CANCEL_SEL_OK), options, 0, UI_CENTER);
}

size_t UI_selected_item(void)
{
	return (UI_list_scroll);
}

void	UI_list_start(void)
{
	UI_mode = UI_LIST;
	UI_needs_repaint = true;
    delay_ms(UI_PRESS_DELAY);
    wheel_pending_flush();
}

void	UI_list_set(size_t i, char *str)
{
	if (!(i < UI_LIST_MAX_SZ)) return;
	if (i > UI_list_size) UI_list_size = i;
	strcpy(UI_list[i], str);
	UI_needs_repaint = true;
}

char*	UI_list_get(size_t i)
{
	if (i > UI_list_size) return (0x00);
	return (UI_list[i]);
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

void UI_putstr_aligned(char *str, byte options, byte offset, byte alignment)
{
	size_t len = 0;
	if (alignment == UI_CENTER) {
		while (str[len++]);
		if (len * 6 > 128)
			offset = 0;
		else
			offset += ((128 - (((len - 1) * 6))) / 2);
		offset++;
	}
	OLED_putstr(str, options, offset);
}
