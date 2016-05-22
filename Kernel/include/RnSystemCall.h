#ifndef RN_KERNEL_SYSTEM_CALL_H_INCLUDED
#define RN_KERNEL_SYSTEM_CALL_H_INCLUDED

#include <RnKernel.h>

#define RN_SYSTEM_CALL_0(name) extern RnResult RN_API RnSystemCall##name();
#define RN_SYSTEM_CALL_1(name, type1) extern RnResult RN_API RnSystemCall##name(type1 arg1);
#define RN_SYSTEM_CALL_2(name, type1, type2) extern RnResult RN_API RnSystemCall##name(type1 arg1, type2 arg2);
#define RN_SYSTEM_CALL_3(name, type1, type2, type3) extern RnResult RN_API RnSystemCall##name(type1 arg1, type2 arg2, type3 arg3);

RN_SYSTEM_CALL_0(Initialize)
RN_SYSTEM_CALL_2(Write, char*, int32_t)
RN_SYSTEM_CALL_2(Read, char*, int32_t*)

#endif // RN_KERNEL_SYSTEM_CALL_H_INCLUDED
