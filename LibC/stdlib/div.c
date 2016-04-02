#include <stdlib.h>

div_t div(int numer, int denom)
{
    div_t result;
    int q = 0;
    int r = 0;
    while(denom*q < numer)
    {
        q++;
    }
    result.quot = --q;
    result.rem = numer - denom*q;
    return result;
}
