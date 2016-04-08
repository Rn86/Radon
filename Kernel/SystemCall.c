#include "SystemCall.h"

#define RN_SYSTEM_CALL_0_IMPL(name) \
int32_t Sys##name()\
{\
	int32_t result = 0;\
	asm volatile("movl %1, %%eax \n"\
				"int $0x7F      \n"\
				"movl %%eax, %0 \n"\
				: "=r" (result) : "r" (rnsc##name));\
	return result;\
}

#define RN_SYSTEM_CALL_1_IMPL(name, type1) \
int32_t Sys##name(type1 arg1)\
{\
	int32_t result = 0;\
	asm volatile("movl %1, %%eax \n"\
				"movl %2, %%ebx \n"\
				"int $0x7F      \n"\
				"movl %%eax, %0 \n"\
				: "=r" (result) : "r" (rnsc##name), "r" (arg1));\
	return result;\
}

#define RN_SYSTEM_CALL_2_IMPL(name, type1, type2) \
int32_t Sys##name(type1 arg1, type2 arg2)\
{\
	int32_t result = 0;\
	asm volatile("movl %1, %%eax \n"\
				"movl %2, %%ebx \n"\
				"movl %3, %%ecx \n"\
				"int $0x7F      \n"\
				"movl %%eax, %0 \n"\
				: "=r" (result) : "r" (rnsc##name), "r" (arg1), "r" (arg2));\
	return result;\
}

#define RN_SYSTEM_CALL_3_IMPL(name, type1, type2, type3) \
int32_t Sys##name(type1 arg1, type2 arg2, type3 arg3)\
{\
	int32_t result = 0;\
	asm volatile("movl %1, %%eax \n"\
				"movl %2, %%ebx \n"\
				"movl %3, %%ecx \n"\
				"movl %4, %%edx \n"\
				"int $0x7F      \n"\
				"movl %%eax, %0 \n"\
				: "=r" (result) : "r" (rnsc##name), "r" (arg1), "r" (arg2), "r" (arg3));\
	return result;\
}

RN_SYSTEM_CALL_0_IMPL(Initialize)
RN_SYSTEM_CALL_1_IMPL(Write, char*)
