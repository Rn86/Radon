#include <stdlib.h>

long int atol(const char *str)
{
    long int result=0;
    while(*str)
    {
        result = result*10;
        if(*str < 48 || *str > 57)
        {
            return 0;
        }
        result+=*str-'0';
        str++;
    }
    return result;
}
