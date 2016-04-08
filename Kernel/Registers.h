#ifndef RN_KERNEL_REGISTERS_H_INCLUDED
#define RN_KERNEL_REGISTERS_H_INCLUDED

#include <stdint.h>

typedef struct Registers_
{
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} Registers;

typedef struct Interupt_
{
	uint32_t interupt, error;
	uint32_t eip, cs, eflags, useresp, ss;
} Interupt;

#endif //!RN_KERNEL_REGISTERS_H_INCLUDED
