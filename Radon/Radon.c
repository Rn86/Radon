#include <stdint.h>
#include "../Kernel/SystemCall.h"

RnKernelResult RN_KERNEL_API RnKernelMain()
{
	RnSystemCallWrite("Hello World");
}
