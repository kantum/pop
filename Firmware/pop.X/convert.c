#include "types.h"
#include "convert.h"

byte convert_ret_l[4];
byte convert_ret_s[2];

byte* convert_long_to_arr(uint64_t val)
{
	convert_ret_l[0] = (val & 0xFF000000) >> 24;
	convert_ret_l[1] = (val & 0x00FF0000) >> 16;
	convert_ret_l[2] = (val & 0x0000FF00) >> 8;
	convert_ret_l[3] = (val & 0x000000FF);
	return (convert_ret_l);
}

uint64_t convert_arr_to_long(byte* arr)
{
	uint64_t ret = 0x00;
	
	ret += (arr[0] << 24);
	ret += (arr[1] << 16);
	ret += (arr[2] << 8);
	ret += (arr[3]);
	return (ret);
}

byte* convert_short_to_arr(uint16_t val)
{
	convert_ret_s[0] = (val & 0xFF00) >> 8;
	convert_ret_s[1] = (val & 0x00FF);
	return (convert_ret_s);
}

uint16_t convert_arr_to_short(byte* arr)
{
	uint16_t ret = 0x00;
	
	ret += (arr[0] << 8);
	ret += (arr[1]);
	return (ret);
}
