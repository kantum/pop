#ifndef CONVERT_H
#define	CONVERT_H

byte* convert_long_to_arr(uint64_t val);
uint64_t convert_arr_to_long(byte* arr);
byte* convert_short_to_arr(uint16_t val);
uint16_t convert_arr_to_short(byte* arr);

#endif	/* CONVERT_H */