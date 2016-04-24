#include <Memory.h>

#define RN_KERNEL_MEMORY_POOL_SIZE 1000000

static int8_t  rnMemoryPool[RN_KERNEL_MEMORY_POOL_SIZE];
static int32_t rnMemoryPoolPointer;

RnKernelResult RN_KERNEL_API RnMemoryInitialize()
{
	int32_t i = 0;
	for (; i < RN_KERNEL_MEMORY_POOL_SIZE; i++)
	{
		rnMemoryPool[i] = 0;
	}
	rnMemoryPoolPointer = 0;
	return 0;
}

RnKernelResult RN_KERNEL_API RnMemoryAllocate(int32_t size, void ** ppBlock)
{
	if (ppBlock)
	{
		void * pBlock = 0;
		if (size > 0 && rnMemoryPoolPointer + size + sizeof(int32_t) < RN_KERNEL_MEMORY_POOL_SIZE)
		{
			rnMemoryPoolPointer += size;
			*(int32_t*)&rnMemoryPool[rnMemoryPoolPointer] = size;
			rnMemoryPoolPointer += sizeof(int32_t);
			pBlock = &rnMemoryPool[rnMemoryPoolPointer];
		}
		*ppBlock = pBlock;
	}
	return 0;
}

RnKernelResult RN_KERNEL_API RnMemoryDeallocate(void * pBlock)
{
	return 0;
}
