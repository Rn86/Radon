#ifndef RN_API_STRING_H_INCLUDED
#define RN_API_STRING_H_INCLUDED

#include <Radon/RnTypes.h>

RN_HANDLE(RnString);

RnResult RN_API RnStringCreate(char * szValue, HRnString * phString);
RnResult RN_API RnStringCreateLength(char * szValue, RnUInt32 length, HRnString * phString);
RnResult RN_API RnStringGetBuffer(HRnString hString, char ** pBuffer);
RnResult RN_API RnStringGetLength(HRnString hString, RnUInt32 * pLength);

#endif // RN_API_STRING_H_INCLUDED
