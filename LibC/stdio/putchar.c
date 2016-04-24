#include <stdio.h>

#include <RnSystemCall.h>

int putchar(int ic)
{
	char c = (char) ic;
	RnSystemCallWrite(&c, sizeof(c));
	return ic;
}
