#ifndef RN_KERNEL_MEMORY_H_INCLUDED
#define RN_KERNEL_MEMORY_H_INCLUDED

#include "Kernel.h"

RnKernelResult RN_KERNEL_API RnMemoryInitialize();
RnKernelResult RN_KERNEL_API RnMemoryAllocate(int32_t size, void ** ppBlock);
RnKernelResult RN_KERNEL_API RnMemoryDeallocate(void * pBlock);

#endif //!RN_MEMORY_H_INCLUDED
