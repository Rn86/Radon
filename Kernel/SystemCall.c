#include <SystemCall.h>
#include <RnKernel.h>

#define RN_SYSTEM_CALL_0_IMPL(name) \
RnResult RN_API RnSystemCall##name()\
{\
	RnResult result = 0;\
	asm volatile(\
		"pusha            \n"\
		"movl %1, %%eax   \n"\
		"xor %%ecx, %%ecx \n"\
		"xor %%ebx, %%ebx \n"\
		"xor %%edx, %%edx \n"\
		"int $0x7F        \n"\
		"movl %%eax, %0   \n"\
		"popa             \n"\
		: "=r" (result) : "r" (rnsc##name) : "%eax", "%ecx", "%ebx", "%edx");\
	return result;\
}

#define RN_SYSTEM_CALL_1_IMPL(name, type1) \
RnResult RN_API RnSystemCall##name(type1 arg1)\
{\
	RnResult result = 0;\
	asm volatile(\
		"pusha            \n"\
		"movl %1, %%eax   \n"\
		"movl %2, %%ecx   \n"\
		"xor %%ebx, %%ebx \n"\
		"xor %%edx, %%edx \n"\
		"int $0x7F        \n"\
		"movl %%eax, %0   \n"\
		"popa             \n"\
		: "=r" (result) : "r" (rnsc##name), "r" (arg1) : "%eax", "%ecx", "%ebx", "%edx");\
	return result;\
}

#define RN_SYSTEM_CALL_2_IMPL(name, type1, type2) \
RnResult RN_API RnSystemCall##name(type1 arg1, type2 arg2)\
{\
	RnResult result = 0;\
	asm volatile(\
		"pusha            \n"\
		"movl %1, %%eax   \n"\
		"movl %2, %%ecx   \n"\
		"movl %3, %%ebx   \n"\
		"xor %%edx, %%edx \n"\
		"int $0x7F        \n"\
		"movl %%eax, %0   \n"\
		"popa             \n"\
		: "=r" (result) : "r" (rnsc##name), "r" (arg1), "r" (arg2) : "%eax", "%ecx", "%ebx", "%edx");\
	return result;\
}

#define RN_SYSTEM_CALL_3_IMPL(name, type1, type2, type3) \
RnResult RN_API RnSystemCall##name(type1 arg1, type2 arg2, type3 arg3)\
{\
	RnResult result = 0;\
	asm volatile(\
		"pusha            \n"\
		"movl %1, %%eax   \n"\
		"movl %2, %%ecx   \n"\
		"movl %3, %%ebx   \n"\
		"movl %4, %%edx   \n"\
		"int $0x7F        \n"\
		"movl %%eax, %0   \n"\
		"popa             \n"\
		: "=r" (result) : "r" (rnsc##name), "r" (arg1), "r" (arg2), "r" (arg3) : "%eax", "%ecx", "%ebx", "%edx");\
	return result;\
}

RN_SYSTEM_CALL_0_IMPL(Initialize)
RN_SYSTEM_CALL_2_IMPL(Write, char*, int32_t)
RN_SYSTEM_CALL_2_IMPL(Read, char*, int32_t*)
