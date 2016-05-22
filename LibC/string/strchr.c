#include <string.h>

char *strchr(const char *str, int c)
{
    char *ptr;
    ptr = (char*)str;
    while(*ptr != c)
    {
        ptr++;
    }
    return ptr;
}
