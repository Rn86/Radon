#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include "Monitor.h"
#include "SystemCall.h"

#include "GlobalDescriptorTable.h"
#include "InteruptDescriptorTable.h"

int32_t KernelInitialize()
{
	GlobalDescriptorTableInitialize();
	InteruptDescriptorTableInitialize();
	SysInitialize();
	return 0;
}

int32_t KernelMain()
{
	int32_t result = SysWrite("Hello, world!\n");
	MonitorWriteInteger(result);

	while (1) {}
	return 0;
}

int32_t KernelCleanup()
{
	return 0;
}


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
	KernelInitialize();
	KernelMain();
	KernelCleanup();
}