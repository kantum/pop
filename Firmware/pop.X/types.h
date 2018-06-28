/* 
 * File:   types.h
 * Author: nburcion@student.42.fr, qdurot@student.42.fr
 *
 * Created on April 22, 2018, 6:45 PM
 */

#ifndef TYPES_H
#define	TYPES_H

typedef unsigned char byte;
//typedef unsigned char bool;
#include <stdbool.h>
#include <xc.h>				// PIC32 Mandatory Include
#include <stdbool.h>		// Contains bool type
#include <stdint.h>			// Contains uint_8 uint_16...
#include <sys/attribs.h>	// Contains __ISR() Macros

//typedef unsigned char size_t;

#define OUTPUT  0
#define INPUT   1

#define HIGH    1
#define LOW     0

#define true    1
#define false   0

#define RISING_EDGE    1
#define FALLING_EDGE    0

#define SYSCLOCK 72000000



#endif	/* TYPES_H */
