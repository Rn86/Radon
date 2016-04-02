#include <stdlib.h>
#include <string.h>

size_t strspn(const char *str1, const char *str2)
{
    size_t result = 0;
    size_t counter = 0;
    char *ptr1;
    char *ptr2;
    ptr1 = str1;
    ptr2 = str2;
    while(*ptr1 != 0)
    {
        if(*ptr1 == *ptr2)
        {
            counter++;
            if(counter > result)
            {
                result = counter;
            }
        }
        else
        {
            counter = 0;
            ptr2 = str2;
            ptr2--;
        }
        ptr1++;
        ptr2++;
    }
    return result;
}
