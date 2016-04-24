#include <stdint.h>
#include <RnSystemCall.h>

RnKernelResult RN_KERNEL_API RnKernelMain()
{
	RnSystemCallWrite("Hello World\n", 12);
	return 0;
}
