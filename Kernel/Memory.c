#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <Memory.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32

typedef struct
{
	uint32_t status;
	uint32_t size;
} RnAlloc;

void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

uint32_t rnLastAlloc = 0;
uint32_t rnHeapEnd = 0;
uint32_t rnHeapBegin = 0;
uint32_t rnMemoryUsed = 0;

RnResult RN_API RnMemoryInitialize(uint32_t kernel_end)
{
	rnLastAlloc = kernel_end + 0x1000;
	rnHeapBegin = rnLastAlloc;
	rnHeapEnd = 0x400000 - (MAX_PAGE_ALIGNED_ALLOCS * 4096);

	return 0;
}

void free(void *mem)
{
	RnAlloc *alloc = (mem - sizeof(RnAlloc));
	rnMemoryUsed -= alloc->size + sizeof(RnAlloc);
	alloc->status = 0;
}

void * malloc(size_t size)
{
	if(!size) return 0;

	uint8_t *mem = (uint8_t *)rnHeapBegin;
	while((uint32_t)mem < rnLastAlloc)
	{
		RnAlloc *a = (RnAlloc *)mem;
		if(!a->size) break;

		if(a->status)
        {
			mem += a->size;
			mem += sizeof(RnAlloc);
			mem += 4;
			continue;
		}

		if(a->size >= size)
		{
			a->status = 1;

			memset(mem + sizeof(RnAlloc), 0, size);
			rnMemoryUsed += size + sizeof(RnAlloc);
			return (char *)(mem + sizeof(RnAlloc));
		}

		mem += a->size;
		mem += sizeof(RnAlloc);
		mem += 4;
	}

	if(rnLastAlloc + size + sizeof(RnAlloc) >= rnHeapEnd)
	{
		return NULL;
	}
	RnAlloc *alloc = (RnAlloc *)rnLastAlloc;
	alloc->status = 1;
	alloc->size = size;

	rnLastAlloc += size;
	rnLastAlloc += sizeof(RnAlloc);
	rnLastAlloc += 4;

	rnMemoryUsed += size + 4 + sizeof(RnAlloc);
	memset((char *)((uint32_t)alloc + sizeof(RnAlloc)), 0, size);
	return (char *)((uint32_t)alloc + sizeof(RnAlloc));
}
