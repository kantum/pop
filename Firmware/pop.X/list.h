/* 
 * File:   list.h
 * Author: bocal
 *
 * Created on July 1, 2018, 1:56 AM
 */

#ifndef LIST_H
#define	LIST_H

struct listItem {
   byte flag;
   char name[50];
   size_t id;
};

bool list_add_item(struct listItem item);
bool list_get_item(size_t index, struct listItem *item);
bool list_set_item(size_t index, struct listItem item);
bool list_clear(void);

#endif	/* LIST_H */

