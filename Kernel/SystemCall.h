#ifndef RN_SYSTEM_CALL_INCLUDED_H
#define RN_SYSTEM_CALL_INCLUDED_H

#include <stdint.h>

typedef enum SystemCall_
{
	rnscInitialize = 0,
	rnscWrite = 1,
} SystemCall;

#define RN_SYSTEM_CALL_0(name) int32_t Sys##name();
#define RN_SYSTEM_CALL_1(name, type1) int32_t Sys##name(type1 arg1);
#define RN_SYSTEM_CALL_2(name, type1, type2) int32_t Sys##name(type1 arg1, type2 arg2);
#define RN_SYSTEM_CALL_3(name, type1, type2, type3) int32_t Sys##name(type1 arg1, type2 arg2, type3 arg3);

RN_SYSTEM_CALL_0(Initialize);
RN_SYSTEM_CALL_1(Write, char*)

#endif //!RN_SYSTEM_CALL_INCLUDED_H