#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <Memory.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32

typedef struct
{
	uint8_t status;
	uint32_t size;
} alloc_t;

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

RnResult RN_API RnMemoryInitialzie(uint32_t kernel_end)
{
	rnLastAlloc = kernel_end + 0x1000;
	rnHeapBegin = rnLastAlloc;
	rnHeapEnd = 0x400000 - (MAX_PAGE_ALIGNED_ALLOCS * 4096);

	return 0;
}

void free(void *mem)
{
	alloc_t *alloc = (mem - sizeof(alloc_t));
	rnMemoryUsed -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}

void * malloc(size_t size)
{
	if(!size) return 0;

	/* Loop through blocks and find a block sized the same or bigger */
	uint8_t *mem = (uint8_t *)rnHeapBegin;
	while((uint32_t)mem < rnLastAlloc)
	{
		alloc_t *a = (alloc_t *)mem;
		/* If the alloc has no size, we have reaced the end of allocation */
		//mprint("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size);
		if(!a->size)
			goto nalloc;
		/* If the alloc has a status of 1 (allocated), then add its size
		 * and the sizeof alloc_t to the memory and continue looking.
		 */
		if(a->status) {
			mem += a->size;
			mem += sizeof(alloc_t);
			mem += 4;
			continue;
		}
		/* If the is not allocated, and its size is bigger or equal to the
		 * requested size, then adjust its size, set status and return the location.
		 */
		if(a->size >= size)
		{
			/* Set to allocated */
			a->status = 1;

			memset(mem + sizeof(alloc_t), 0, size);
			rnMemoryUsed += size + sizeof(alloc_t);
			return (char *)(mem + sizeof(alloc_t));
		}
		/* If it isn't allocated, but the size is not good, then
		 * add its size and the sizeof alloc_t to the pointer and
		 * continue;
		 */
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

	nalloc:;
	if(rnLastAlloc + size + sizeof(alloc_t) >= rnHeapEnd)
	{
		return NULL;
	}
	alloc_t *alloc = (alloc_t *)rnLastAlloc;
	alloc->status = 1;
	alloc->size = size;

	rnLastAlloc += size;
	rnLastAlloc += sizeof(alloc_t);
	rnLastAlloc += 4;

	rnMemoryUsed += size + 4 + sizeof(alloc_t);
	memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
	return (char *)((uint32_t)alloc + sizeof(alloc_t));
}
