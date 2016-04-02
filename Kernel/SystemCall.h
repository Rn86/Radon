#ifndef RN_SYSTEM_CALL_INCLUDED_H
#define RN_SYSTEM_CALL_INCLUDED_H

typedef enum SystemCall_
{
	rnscWrite = 1,
} SystemCall;

#define RN_SYSTEM_CALL_1(name, type1) \
int name(type1 arg1)\
{\
	asm volatile("movl %0, %%eax" :: "r" (rnsc##name));\
	asm volatile("movl %0, %%ebx" :: "r" (arg1));\
	asm volatile("int $0x7F");\
	return 0;\
}

#define RN_SYSTEM_CALL_2(name, type1, type2) \
int name(type1 arg1)\
{\
	asm volatile("movl %0, %%eax" :: "r" (rnsc##name));\
	asm volatile("movl %0, %%ebx" :: "r" (arg1));\
	asm volatile("int $0x7F");\
	return 0;\
}

RN_SYSTEM_CALL_1(Write, char*)

#endif //!RN_SYSTEM_CALL_INCLUDED_H