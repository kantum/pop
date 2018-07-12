/* 
 * File:   UI.h
 * Author: bocal
 *
 * Created on July 3, 2018, 12:20 PM
 */

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

void     UI_init(void);
void	 UI_paint_list(void);
bool	 UI_scroll(byte dir);
void     UI_set_scroll(int32_t sc);
void     UI_repaint(void);
byte	 UI_message(char *msg, byte settings, size_t timeout);
byte     UI_prompt(char *msg);
int32_t  UI_number(char *msg, int32_t val, int32_t min, int32_t max, int32_t step, void (*callback)(byte));
uint16_t UI_distance(void);
void     UI_paint_number(char *str, int32_t val);
void     UI_paint_prompt(char *str, byte selected);
void	 UI_paint_msg(char *str);
size_t	 UI_selected_item(void);
void	 UI_list_start(void);
void	 UI_list_set(size_t i, char *str);
void	 UI_list_clear(void);
void	 UI_paint_list(void);
void     UI_putstr_aligned(char *str, byte options, byte offset, byte alignment);

#endif	/* UI_H */

