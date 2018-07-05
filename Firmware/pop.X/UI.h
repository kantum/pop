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

void	UI_paint_list(void);
void	UI_scroll(byte dir);
void	UI_repaint(void);
void	UI_list_start(void);
void	UI_list_set(size_t i, char* str);
void	UI_list_clear(void);

#define SCROLL_UP   0x00
#define SCROLL_DOWN 0x01
#define SCROLL_RST  0x02

#define UI_NONE     0x00
#define UI_LIST     0x01
#define UI_MSG      0x02

#define UI_LIST_MAX_SZ 100

#endif	/* UI_H */

