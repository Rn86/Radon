#ifndef RN_SYSTEM_CALL_INCLUDED_H
#define RN_SYSTEM_CALL_INCLUDED_H

#include "Kernel.h"

typedef enum RnSystemCall_
{
	rnscInitialize = 0,
	rnscWrite = 1,
	rnscAllocate = 2,
	rnscDeallocate = 3,
} RnSystemCall;

#define RN_SYSTEM_CALL_0(name) RnKernelResult RN_KERNEL_API RnSystemCall##name();
#define RN_SYSTEM_CALL_1(name, type1) RnKernelResult RN_KERNEL_API RnSystemCall##name(type1 arg1);
#define RN_SYSTEM_CALL_2(name, type1, type2) RnKernelResult RN_KERNEL_API RnSystemCall##name(type1 arg1, type2 arg2);
#define RN_SYSTEM_CALL_3(name, type1, type2, type3) RnKernelResult RN_KERNEL_API RnSystemCall##name(type1 arg1, type2 arg2, type3 arg3);

RN_SYSTEM_CALL_0(Initialize)
RN_SYSTEM_CALL_1(Write, char*)
RN_SYSTEM_CALL_2(Allocate, int32_t, void **)
RN_SYSTEM_CALL_1(Deallocate, void *)

#endif //!RN_SYSTEM_CALL_INCLUDED_H