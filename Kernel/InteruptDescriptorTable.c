#include "InteruptDescriptorTable.h"
#include "InteruptServiceRoutine.h"

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

extern void InteruptDescriptorTableFlush(uint32_t);

static void InteruptDescriptorTableSetGate(uint8_t, uint32_t, uint16_t, uint8_t);

static void* memset(void* bufptr, int value, uint32_t size)
{
	uint32_t i = 0;
	unsigned char* buf = (unsigned char*)bufptr;
	for (i = 0; i < size; i++)
		buf[i] = (unsigned char)value;
	return bufptr;
}

#define RN_ISR_HANDLE(nr) InteruptServiceRoutine_##nr

int32_t InteruptDescriptorTableInitialize()
{
	idtPointer.limit = sizeof(IdtEntry) * 256 - 1;
	idtPointer.base = (uint32_t)&idtEntries;

	memset((uint8_t*)&idtEntries, 0, sizeof(IdtEntry) * 256);

	InteruptDescriptorTableSetGate(0,   (uint32_t)InteruptServiceRoutine_0,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(1,   (uint32_t)InteruptServiceRoutine_1,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(2,   (uint32_t)InteruptServiceRoutine_2,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(3,   (uint32_t)InteruptServiceRoutine_3,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(4,   (uint32_t)InteruptServiceRoutine_4,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(5,   (uint32_t)InteruptServiceRoutine_5,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(6,   (uint32_t)InteruptServiceRoutine_6,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(7,   (uint32_t)InteruptServiceRoutine_7,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(8,   (uint32_t)InteruptServiceRoutine_8,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(9,   (uint32_t)InteruptServiceRoutine_9,   0x08, 0x8E);
	InteruptDescriptorTableSetGate(10,  (uint32_t)InteruptServiceRoutine_10,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(11,  (uint32_t)InteruptServiceRoutine_11,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(12,  (uint32_t)InteruptServiceRoutine_12,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(13,  (uint32_t)InteruptServiceRoutine_13,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(14,  (uint32_t)InteruptServiceRoutine_14,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(15,  (uint32_t)InteruptServiceRoutine_15,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(16,  (uint32_t)InteruptServiceRoutine_16,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(17,  (uint32_t)InteruptServiceRoutine_17,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(18,  (uint32_t)InteruptServiceRoutine_18,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(19,  (uint32_t)InteruptServiceRoutine_18,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(20,  (uint32_t)InteruptServiceRoutine_20,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(21,  (uint32_t)InteruptServiceRoutine_21,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(22,  (uint32_t)InteruptServiceRoutine_22,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(23,  (uint32_t)InteruptServiceRoutine_23,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(24,  (uint32_t)InteruptServiceRoutine_24,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(25,  (uint32_t)InteruptServiceRoutine_25,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(26,  (uint32_t)InteruptServiceRoutine_26,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(27,  (uint32_t)InteruptServiceRoutine_27,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(28,  (uint32_t)InteruptServiceRoutine_28,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(29,  (uint32_t)InteruptServiceRoutine_29,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(30,  (uint32_t)InteruptServiceRoutine_30,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(31,  (uint32_t)InteruptServiceRoutine_31,  0x08, 0x8E);
	InteruptDescriptorTableSetGate(127, (uint32_t)InteruptServiceRoutine_127, 0x08, 0x8E);

	InteruptDescriptorTableFlush((uint32_t)&idtPointer);

	return 0;
}

static void InteruptDescriptorTableSetGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idtEntries[num].base_lo = base & 0xFFFF;
	idtEntries[num].base_hi = (base >> 16) & 0xFFFF;

	idtEntries[num].sel = sel;
	idtEntries[num].always0 = 0;

	idtEntries[num].flags = flags;
}
