#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <GlobalDescriptorTable.h>
#include <InteruptDescriptorTable.h>
#include <InteruptServiceRoutine.h>
#include <InteruptRequest.h>

#include <Tasking.h>
#include <Memory.h>

#include <Timer.h>
#include <Keyboard.h>

#include <Monitor.h>
#include <SystemCall.h>
#include <RnSystemCall.h>

static uint32_t rnKernelEnd;

static char rnBanner[] =
{
" _____           _             \n"
"|  __ \\         | |            \n"
"| |__) |__ _  __| | ___  _ __  \n"
"|  _  // _` |/ _` |/ _ \\| '_ \\ \n"
"| | \\ \\ (_| | (_| | (_) | | | |\n"
"|_|  \\_\\__,_|\\__,_|\\___/|_| |_|\n"
"Authors:\n"
"    Rn86\n"
"    ragutislt\n"
"    Shalifar\n"
"\n"
};

RnResult RN_API RnKernelMain();

void RN_API RnKernelMainProxy()
{
    RnKernelMain();
}

RnResult RN_API RnKernelInitialize()
{
    RnMonitorInitialize();

    RnMonitorWrite(rnBanner);

	RnGlobalDescriptorTableInitialize();
	RnInteruptDescriptorTableInitialize();
    RnInteruptServiceRoutineInitialize();
	RnInteruptRequestInitialize();

	RnMemoryInitialize(&rnKernelEnd);
    RnPagingInitialize();

    RnTimerInitialize();
    RnKeyboardInitialize();

    RnTaskingInitialize(&RnKernelMainProxy);

	return 0;
}

RnResult RN_API RnKernelCleanup()
{
	return 0;
}

void kernel_main()
{
	RnKernelInitialize();
	//RnKernelMain();
	//RnKernelCleanup();
}
