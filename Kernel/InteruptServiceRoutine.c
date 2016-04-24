#include <SystemCall.h>
#include <Registers.h>
#include <Monitor.h>
#include <Memory.h>

#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CHANNEL1      0x41  //PIT Channels 1's Data Register Port, we wont be using this here
#define PIT_CHANNEL2     0x42  //PIT Channels 2's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port

static void outportb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void timer_set(int hz)
{
	int divisor = 1193180 / hz;
	outportb(PIT_CMDREG, 0x36);
	outportb(PIT_CHANNEL0, divisor & 0xFF);
	outportb(PIT_CHANNEL0, divisor >> 8);
}

void InteruptServiceRoutine(uint32_t ds, Registers registers, Interupt interupt)
{
	RnKernelResult result = 0;

	if (interupt.error)
	{
		RnMonitorWrite("Error interupt: ");
		RnMonitorWriteInteger(interupt.interupt);
		RnMonitorWrite("\n");

		RnMonitorWrite("Error code: ");
		RnMonitorWriteInteger(interupt.error);
		RnMonitorWrite("\n");
	}
	else if (interupt.interupt == 0x7F)
	{
		switch ((RnSystemCall)registers.eax)
		{
		case rnscInitialize:
		{
			RnMemoryInitialize();
			RnMonitorInitialize();
			timer_set(100);
			break;
		}
		case rnscWrite:
		{
			result = RnMonitorWriteLength((char*)registers.ecx, (int32_t)registers.ebx);
			break;
		}
		case rnscAllocate:
		{
			result = RnMemoryAllocate((int32_t)registers.ecx, (void**)registers.ebx);
			break;
		}
		case rnscDeallocate:
		{
			result = RnMemoryDeallocate((void*)registers.ecx);
			break;
		}
		default:
		{
			RnMonitorWrite("eax: ");
			RnMonitorWriteInteger(registers.eax);
			RnMonitorWrite("\n");

			RnMonitorWrite("ebx: ");
			RnMonitorWriteInteger(registers.ebx);
			RnMonitorWrite("\n");

			RnMonitorWrite("ecx: ");
			RnMonitorWriteInteger(registers.ecx);
			RnMonitorWrite("\n");

			RnMonitorWrite("edx: ");
			RnMonitorWriteInteger(registers.edx);
			RnMonitorWrite("\n");

			break;
		}
		}
	}
	else
	{
		RnMonitorWrite("Interupt: ");
		RnMonitorWriteInteger(interupt.interupt);
		RnMonitorWrite("\n");
	}

	asm volatile("movl %0, %%eax \n" :: "r" (result) : "%eax");
}
