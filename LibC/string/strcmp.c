#include <string.h>

int strcmp(const char* s1, const char* s2)
{
    int result = 0;
    while(*s1 == *s2)
    {
        s1++; s2++;
    }
    if(*(unsigned char *)s1 < *(unsigned char *)s2)
    {
        result = -1;
    }
    else
    {
        result = 1;
    }
    return result;
}

