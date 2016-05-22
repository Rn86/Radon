#include <memory.h>

#include <stdint.h>
#include <stdio.h>

static uint32_t * rnPageDirectory = NULL;
static uint32_t rnPageDirectoryLocation = 0;
static uint32_t * rnLastPage = NULL;

void RnPagingMapVirtualToPhys(uint32_t virt, uint32_t phys)
{
	uint16_t id = virt >> 22;
	for(int i = 0; i < 1024; i++)
	{
		rnLastPage[i] = phys | 3;
		phys += 4096;
	}
	rnPageDirectory[id] = ((uint32_t)rnLastPage) | 3;
	rnLastPage = (uint32_t *)(((uint32_t)rnLastPage) + 4096);
}

RnResult RN_API RnPagingEnable()
{
	asm volatile("mov %%eax, %%cr3": :"a"(rnPageDirectoryLocation));
	asm volatile("mov %cr0, %eax");
	asm volatile("orl $0x80000000, %eax");
	asm volatile("mov %eax, %cr0");

	return 0;
}

RnResult RN_API RnPagingInitialize()
{
	rnPageDirectory = (uint32_t*)0x400000;
	rnPageDirectoryLocation = (uint32_t)rnPageDirectory;
	rnLastPage = (uint32_t *)0x404000;
	for(int i = 0; i < 1024; i++)
	{
		rnPageDirectory[i] = 0 | 2;
	}
	RnPagingMapVirtualToPhys(0, 0);
	RnPagingMapVirtualToPhys(0x400000, 0x400000);
	RnPagingEnable();

	return 0;
}
