#include <Tasking.h>
#include <Monitor.h>
#include <Memory.h>

static RnTask * rnRunningTask = NULL;
static RnTask rnMainTask;

static RnResult RN_API RnTaskInitialize(RnTask *task, void (*main)(), uint32_t flags, uint32_t *pagedir);

RnResult RN_API RnTaskingInitialize()
{
    // Get EFLAGS and CR3
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(rnMainTask.regs.cr3)::"%eax");
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(rnMainTask.regs.eflags)::"%eax");

    rnRunningTask = &rnMainTask;

    return 0;
}

RnResult RN_API RnTaskCreate(void (*main)(), RnTask * task)
{
    RnTaskInitialize(task, main, rnMainTask.regs.eflags, (uint32_t*)rnMainTask.regs.cr3);

    rnMainTask.next = &rnMainTask;

    return 0;
}

RnResult RN_API RnTaskingAdd(RnTask * task)
{
    RnTask * next = rnMainTask.next;
    rnMainTask.next = task;
    task->next = next;

    return 0;
}

void RN_API RnTaskingSwitchTask()
{
    RnTask *last = rnRunningTask;
    rnRunningTask = rnRunningTask->next;
    RnTaskingSwitchContext(&last->regs, &rnRunningTask->regs);
}

static RnResult RN_API RnTaskInitialize(RnTask *task, void (*main)(), uint32_t flags, uint32_t *pagedir)
{
    void * stack = 0;
    stack = malloc(1024);

    task->next = NULL;
    task->param = NULL;

    task->regs.eax = 0;
    task->regs.ebx = 0;
    task->regs.ecx = 0;
    task->regs.edx = 0;
    task->regs.esi = 0;
    task->regs.edi = 0;
    task->regs.eflags = flags;
    task->regs.eip = (uint32_t) main;
    task->regs.cr3 = (uint32_t) pagedir;
    task->regs.esp = (uint32_t) stack + 0x1024;
    task->next = 0;

    return 0;
}
