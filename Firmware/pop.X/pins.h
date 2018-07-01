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
#define ShiftRegisterLatch_LAT      LATEbits.LATE2
#define ShiftRegisterLatch_TRIS     TRISEbits.TRISE2

#define ShiftRegisterData_LAT       LATEbits.LATE3
#define ShiftRegisterData_TRIS      TRISEbits.TRISE3

#define ShiftRegisterClock_LAT      LATEbits.LATE4
#define ShiftRegisterClock_TRIS     TRISEbits.TRISE4
/* [shiftreg] */

/* [leds]  */
#define LED_R_LAT                   LATDbits.LATD2
#define LED_R_TRIS                  TRISDbits.TRISD2

#define LED_G_LAT                   LATDbits.LATD3
#define LED_G_TRIS                  TRISDbits.TRISD3

#define LED_B_LAT                   LATDbits.LATD4
#define LED_B_TRIS                  TRISDbits.TRISD4
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

