#include <Tasking.h>
#include <Monitor.h>
#include <Memory.h>
#include <InteruptRequest.h>

#include <RnSystemCall.h>

#include <stdarg.h>

static RnTask * rnRunningTask = NULL;
static RnTask rnMainTask;
static bool rnTaskingInitialized = false;

static RnResult RN_API RnTaskInitialize(RnTask *task, void (*main)(), uint32_t flags, uint32_t *pagedir);

RnResult RN_API RnTaskingInitialize(void (RN_API * main)())
{
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(rnMainTask.regs.cr3)::"%eax");
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(rnMainTask.regs.eflags)::"%eax");

    RnTaskCreate(main, &rnMainTask);

    rnRunningTask = &rnMainTask;

    rnTaskingInitialized = true;

    asm volatile("mov %%eax, %%esp": :"a"(rnRunningTask->regs.esp));
	asm volatile("pop %gs");
	asm volatile("pop %fs");
	asm volatile("pop %es");
	asm volatile("pop %ds");
	asm volatile("pop %ebp");
	asm volatile("pop %edi");
	asm volatile("pop %esi");
	asm volatile("pop %edx");
	asm volatile("pop %ecx");
	asm volatile("pop %ebx");
	asm volatile("pop %eax");
	asm volatile("ret");

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
    if (!rnTaskingInitialized) return;

    asm volatile("push %eax");
	asm volatile("push %ebx");
	asm volatile("push %ecx");
	asm volatile("push %edx");
	asm volatile("push %esi");
	asm volatile("push %edi");
	asm volatile("push %ebp");
	asm volatile("push %ds");
	asm volatile("push %es");
	asm volatile("push %fs");
	asm volatile("push %gs");
	asm volatile("mov %%esp, %%eax":"=a"(rnRunningTask->regs.esp));
	rnRunningTask = rnRunningTask->next;
	asm volatile("mov %%eax, %%cr3": :"a"(rnRunningTask->regs.cr3));
	asm volatile("mov %%eax, %%esp": :"a"(rnRunningTask->regs.esp));
	asm volatile("pop %gs");
	asm volatile("pop %fs");
	asm volatile("pop %es");
	asm volatile("pop %ds");
	asm volatile("pop %ebp");
	asm volatile("pop %edi");
	asm volatile("pop %esi");
	asm volatile("out %%al, %%dx": :"d"(0x20), "a"(0x20)); // send EoI to master PIC
	asm volatile("pop %edx");
	asm volatile("pop %ecx");
	asm volatile("pop %ebx");
	asm volatile("pop %eax");
	asm volatile("ret");
}

static RnResult RN_API RnTaskInitialize(RnTask *task, void (*main)(), uint32_t flags, uint32_t *pagedir)
{
    task->regs.esp = (uint32_t)malloc(1024);
    uint32_t* stack = (uint32_t *)(task->regs.esp + 1024);
	*--stack = flags; // eflags
	*--stack = 0x8; // cs
	*--stack = (uint32_t)main; // eip
	*--stack = 0; // eax
	*--stack = 0; // ebx
	*--stack = 0; // ecx;
	*--stack = 0; //edx
	*--stack = 0; //esi
	*--stack = 0; //edi
	*--stack = task->regs.esp + 1024; //ebp
	*--stack = 0x10; // ds
	*--stack = 0x10; // fs
	*--stack = 0x10; // es
	*--stack = 0x10; // gs
	task->regs.esp = (uint32_t)stack;
	task->regs.cr3 = (uint32_t)pagedir;

    task->next = NULL;
    task->param = NULL;

    return 0;
}
