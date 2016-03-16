#include <string.h>

char *strstr(const char *haystack, const char *needle)
{
    char *ptr1;
    char *ptr2;
    ptr1 = haystack;
    ptr2 = needle;

    int counter = 0;
    int n_length = strlen(needle);

    while(*ptr1 != 0)
    {
        if(*ptr1 == *ptr2)
        {
            counter++;
            if(counter == n_length)
            {
                return ptr1-n_length+1;
            }
            ptr2++;
        }
        else
        {
            counter = 0;
            ptr2 = needle;
        }
        ptr1++;
    }
    return NULL;
}
