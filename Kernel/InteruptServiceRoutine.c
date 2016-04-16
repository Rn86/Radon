#include "Registers.h"
#include "SystemCall.h"
#include "Monitor.h"
#include "Memory.h"

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
