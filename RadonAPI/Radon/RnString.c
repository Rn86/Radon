#include <Radon/RnString.h>
#include <stdlib.h>

typedef struct RnString_
{
    char * szValue;
    RnUInt32 length;
} RnString;

RnResult RN_API RnStringCreate(char * szValue, HRnString * phString)
{
    RnUInt32 length = 0;
    if (!szValue) return -1;
    while(szValue[length])
        length++;
    return RnStringCreateLength(szValue, length, phString);
}

RnResult RN_API RnStringCreateLength(char * szValue, RnUInt32 length, HRnString * phString)
{
    return 0;
}

RnResult RN_API RnStringGetBuffer(HRnString hString, char ** pBuffer)
{
    return 0;
}

RnResult RN_API RnStringGetLength(HRnString hString, RnUInt32 * pLength)
{
    return 0;
}
