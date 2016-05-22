#include <InteruptDescriptorTable.h>
#include <InteruptServiceRoutine.h>

struct IdtEntry_
{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t  always0;
	uint8_t  flags;
	uint16_t base_hi;
} __attribute__((packed));

typedef struct IdtEntry_ IdtEntry;

struct IdtPointer_
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct IdtPointer_ IdtPointer;

static IdtEntry idtEntries[256];
static IdtPointer idtPointer;

extern void RN_API RnInteruptDescriptorTableFlush(uint32_t);

static void* memset(void* bufptr, int value, uint32_t size)
{
	uint32_t i = 0;
	unsigned char* buf = (unsigned char*)bufptr;
	for (i = 0; i < size; i++)
		buf[i] = (unsigned char)value;
	return bufptr;
}

RnResult RN_API RnInteruptDescriptorTableInitialize()
{
	idtPointer.limit = sizeof(IdtEntry) * 256 - 1;
	idtPointer.base = (uint32_t)&idtEntries;

	memset((uint8_t*)&idtEntries, 0, sizeof(IdtEntry) * 256);

	RnInteruptDescriptorTableFlush((uint32_t)&idtPointer);

    return 0;
}

RnResult RN_API RnInteruptDescriptorTableSetGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idtEntries[num].base_lo = base & 0xFFFF;
	idtEntries[num].base_hi = (base >> 16) & 0xFFFF;

	idtEntries[num].sel = sel;
	idtEntries[num].always0 = 0;

	idtEntries[num].flags = flags;

	return 0;
}
