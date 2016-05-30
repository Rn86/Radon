#ifndef RN_KERNEL_TASK_H_INCLUDED
#define RN_KERNEL_TASK_H_INCLUDED

#include <RnKernel.h>

typedef struct
{
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} RnTaskRegisters;

typedef struct RnTask_
{
    RnTaskRegisters regs;
    void * param;
    struct RnTask_ * next;
} RnTask;

RnResult RN_API RnTaskingInitialize(void (RN_API * main)());

RnResult RN_API RnTaskCreate(void (*main)(), RnTask * task);
RnResult RN_API RnTaskingAdd(RnTask * task);

void RN_API RnTaskingSwitchTask();

#endif // RN_KERNEL_TASK_H_INCLUDED
