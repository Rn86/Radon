#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include <GlobalDescriptorTable.h>
#include <InteruptDescriptorTable.h>
#include <Monitor.h>
#include <RnSystemCall.h>

RnKernelResult RN_KERNEL_API RnKernelInitialize()
{
	GlobalDescriptorTableInitialize();
	InteruptDescriptorTableInitialize();
	RnSystemCallInitialize();

	return 0;
}

RnKernelResult RN_KERNEL_API RnKernelCleanup()
{
	return 0;
}

RnKernelResult RN_KERNEL_API RnKernelMain();

void kernel_main()
{
	RnKernelInitialize();
	RnKernelMain();
	RnKernelCleanup();
}
