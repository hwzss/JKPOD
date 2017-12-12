#include "LCOpenApi_algorithm.h"

namespace LCOpenApi{
// base64 tables 
static char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 

int common_algorithm_base64(char *data, int len, char *out)
{
	unsigned char *buf = (unsigned char *)data;

	if (!data || len <= 0 || !out)
	{
		return -1;
	}

	while (len >= 3) 
	{ 
		*out++ = basis_64[buf[0] >> 2]; 
		*out++ = basis_64[((buf[0] << 4) & 0x30) | (buf[1] >> 4)]; 
		*out++ = basis_64[((buf[1] << 2) & 0x3C) | (buf[2] >> 6)]; 
		*out++ = basis_64[buf[2] & 0x3F]; 
		buf += 3; 
		len -= 3; 
	}

	if (len > 0) 
	{ 
		unsigned char oval = 0;  

		*out++ = basis_64[buf[0] >> 2]; 
		oval = (buf[0] << 4) & 0x30 ; 
		if (len > 1) oval |= buf[1] >> 4; 
		*out++ = basis_64[oval]; 
		*out++ = (len < 2) ? '=' : basis_64[(buf[1] << 2) & 0x3C]; 
		*out++ = '='; 
	} 

	*out = 0;  

	return 0;
}

}