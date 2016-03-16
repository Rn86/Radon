#include <string.h>

char *strchr(const char *str, int c)
{
    char *ptr;
    ptr = str;
    while(*ptr != c)
    {
        ptr++;
    }
    return ptr;
}
