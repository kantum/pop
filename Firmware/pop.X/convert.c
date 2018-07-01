#include "types.h"
#include "convert.h"

byte convert_ret[4];

byte* convert_long_to_arr(unsigned long val)
{
	convert_ret[0] = (val & 0xFF000000) >> 24;
	convert_ret[1] = (val & 0x00FF0000) >> 16;
	convert_ret[2] = (val & 0x0000FF00) >> 8;
	convert_ret[3] = (val & 0x000000FF);
	
	return (convert_ret);
}

unsigned long convert_arr_to_long(byte* arr)
{
	unsigned long ret = 0x00;
	
	ret += (arr[0] << 24);
	ret += (arr[1] << 16);
	ret += (arr[2] << 8);
	ret += (arr[3]);
	return (ret);
}


