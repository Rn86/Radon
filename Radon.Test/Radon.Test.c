#include <stdint.h>
#include <stdio.h>

#include <RnKernel.h>
#include <RnSystemCall.h>

#include "../Kernel/Tasking.h"
#include "../Kernel/Monitor.h"

RnTask task1;
RnTask task2;

static void Task1()
{
    char buffer[256] = { 0 };

    while (1)
    {
        if (!task1.param)
        {
            printf("Task1: ");
            gets(buffer);
            task1.param = (void*)buffer;
        }
        RnTaskingSwitchTask();
    }
}

static void Task2()
{
    while(1)
    {
        if (task1.param)
        {
            printf("Task2: %s\n", (char*)task1.param);
            task1.param = NULL;
        }
        RnTaskingSwitchTask();
    }
}

RnResult RN_API RnKernelMain()
{
    RnTaskCreate(Task1, &task1);
    RnTaskCreate(Task2, &task2);

    RnTaskingAdd(&task1);
    RnTaskingAdd(&task2);

	while (1)
    {
        RnTaskingSwitchTask();
    }

	return 0;
}
