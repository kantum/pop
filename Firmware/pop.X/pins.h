/* 
 * File:   pins.h
 * Author: nburcion@student.42.fr
 *
 * Created on June 27, 2018, 4:25 AM
 */

#ifndef PINS_H
#define	PINS_H

/* [SD]  */
#define SPI_SS_SD_TRIS              TRISFbits.TRISF1
#define SPI_SS_SD_LAT               LATFbits.LATF1
/* [SD] */

/* [shiftreg]  */
/* [shiftreg] */

/* [leds]  */
/* [leds]  */

/* [wheel]  */
#define WHEEL_R_PORT                PORTDbits.RD9
#define WHEEL_R_TRIS                TRISDbits.TRISD9

#define WHEEL_L_PORT                PORTDbits.RD10
#define WHEEL_L_TRIS                TRISDbits.TRISD10

#define WHEEL_P_PORT                PORTDbits.RD11
#define WHEEL_P_TRIS                TRISDbits.TRISD11
/* [wheel]  */

#endif	/* PINS_H */

