#include <string.h>

void* strcpy(void* restrict dstptr, const void* restrict srcptr)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;

	size_t i = 0;
	while (src[i] != '\0')
	{
		dst[i++] = src[i];
	}
	
	return dstptr;
}
