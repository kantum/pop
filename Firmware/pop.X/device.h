/* 
 * File:   device.h
 * Author: bocal
 *
 * Created on July 16, 2018, 9:05 PM
 */

#ifndef DEVICE_H
#define	DEVICE_H

#include <p32xxxx.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */

void device_unlock(void);
void device_sleep(void);

#endif	/* DEVICE_H */

