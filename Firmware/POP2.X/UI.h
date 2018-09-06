#ifndef UI_H
#define	UI_H

#include "types.h"
#include "screen.h"
#include "wheel.h"
#include "FAT32.h"
#include "settings.h"

#define SCROLL_UP   0x00
#define SCROLL_DOWN 0x01
#define SCROLL_RST  0x02

#define UI_NONE     0x00
#define UI_LIST     0x01
#define UI_MSG      0x02

#define UI_MSG_LINE_LEN 12

#define UI_DEFAULT					0b00000000
#define UI_DISSMISSED_BY_ALL_EVENTS 0b00000001
#define UI_IGNORE_EVENTS	        0b00000010

#define UI_EXPIRED_TMOUT            0b00000000
#define UI_OK                       0b00000001
#define UI_CANCEL                   0b00000010

#define UI_LIST_MAX_SZ              100
#define UI_PRESS_DELAY              250

#define UI_LEFT                     0x00
#define UI_CENTER                   0x01

#define UI_KB_REGULAR               0x00
#define UI_KB_CAPS                  0x01
#define UI_KB_SPECIAL               0x02

char* UI_BUFF_TMP;
char UI_BUFF_1[1024];
char UI_BUFF_2[1024];
char UI_BUFF_3[1024];
char UI_BUFF_4[1024];
char UI_BUFF_5[1024];
char UI_BUFF_6[1024];
char UI_BUFF_7[1024];
char UI_BUFF_8[1024];
char UI_BUFF_9[1024];
char UI_BUFF_10[1024];
char UI_BUFF_11[1024];
char UI_BUFF_12[1024];
char UI_BUFF_13[1024];
char UI_BUFF_14[1024];
char UI_BUFF_15[1024];
char UI_BUFF_16[1024];
char UI_BUFF_17[1024];
char UI_BUFF_18[1024];
char UI_BUFF_19[1024];
char UI_BUFF_20[1024];
char UI_BUFF_21[1024];

size_t	UI_list_size = 0;
bool    UI_sun_loaded = true;

void     UI_init(void);
void	 UI_paint_list(void);
bool	 UI_scroll(byte dir);
void     UI_set_scroll(int32_t sc);
void     UI_repaint(void);
byte	 UI_message(char *msg, byte settings, size_t timeout);
byte     UI_prompt(char *msg);
int32_t  UI_number(char *msg, int32_t val, int32_t min, int32_t max, int32_t step, void (*callback)(byte));
uint16_t UI_distance(void);
uint64_t UI_password(char *str, byte len);
byte     UI_keyboard_paint(char str[20], size_t row, size_t col, byte kb_, byte len);
void     UI_paint_pass(char *str, char *digits, byte selected, bool blinking);
void     UI_paint_number(char *str, int32_t val);
void     UI_paint_prompt(char *str, byte selected);
void	 UI_paint_msg(char *str);
size_t	 UI_selected_item(void);
void	 UI_list_start(void);
void	 UI_list_set(size_t i, char *str);
void	 UI_list_clear(void);
void	 UI_paint_list(void);
void     UI_putstr_aligned(char *str, byte options, byte offset, byte alignment);
void     UI_animate_blink(byte step);
bool	 UI_load_buff(char *buff, char *path);

#endif	/* UI_H */