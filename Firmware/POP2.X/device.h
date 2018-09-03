#ifndef DEVICE_H
#define	DEVICE_H

#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "types.h"

#define DEVICE_SLEEP_TMOUT		20000

void device_unlock(void);
void device_sleep(void);
bool device_authorize(char *str);

#endif	/* DEVICE_H */