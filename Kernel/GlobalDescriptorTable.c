#include "GlobalDescriptorTable.h"

struct GdtEntry_
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_middle;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  base_high;
} __attribute__((packed));

typedef struct GdtEntry_ GdtEntry;

struct GdtPointer_
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct GdtPointer_ GdtPointer;

GdtEntry gdtEntries[5];
GdtPointer gdtPointer;

extern void GlobalDescriptorTableFlush(uint32_t);

static void GlobalDescriptorTableSetGate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

int32_t GlobalDescriptorTableInitialize()
{
	gdtPointer.limit = (sizeof(GdtEntry) * 5) - 1;
	gdtPointer.base = (uint32_t)&gdtEntries;

	GlobalDescriptorTableSetGate(0, 0, 0, 0, 0);
	GlobalDescriptorTableSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	GlobalDescriptorTableSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	GlobalDescriptorTableSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	GlobalDescriptorTableSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	GlobalDescriptorTableFlush((uint32_t)&gdtPointer);

	return 0;
}

static void GlobalDescriptorTableSetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdtEntries[num].base_low = (base & 0xFFFF);
	gdtEntries[num].base_middle = (base >> 16) & 0xFF;
	gdtEntries[num].base_high = (base >> 24) & 0xFF;

	gdtEntries[num].limit_low = (limit & 0xFFFF);
	gdtEntries[num].granularity = (limit >> 16) & 0x0F;

	gdtEntries[num].granularity |= gran & 0xF0;
	gdtEntries[num].access = access;
}
