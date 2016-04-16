#include "Registers.h"
#include "SystemCall.h"
#include "Monitor.h"
#include "Memory.h"

void InteruptServiceRoutine(uint32_t ds, Registers regsisters, Interupt interupt)
{
	RnKernelResult result = 0;

	if (interupt.error)
	{
		MonitorWrite("Error interupt: ");
		MonitorWriteInteger(interupt.interupt);
		MonitorWrite("\n");

		MonitorWrite("Error code: ");
		MonitorWriteInteger(interupt.error);
		MonitorWrite("\n");
	}
	else if (interupt.interupt == 0x7F)
	{
		switch ((RnSystemCall)regsisters.eax)
		{
		case rnscInitialize:
		{
			RnMemoryInitialize();
			RnMonitorInitialize();
			break;
		}
		case rnscWrite:
		{
			result = MonitorWrite((char*)regsisters.ebx);
			break;
		}
		case rnscAllocate:
		{
			result = RnMemoryAllocate((int32_t)regsisters.ebx, (void**)regsisters.ecx);
			break;
		}
		case rnscDeallocate:
		{
			result = RnMemoryDeallocate((void*)regsisters.ebx);
			break;
		}
		default:
		{
			MonitorWrite("eax: ");
			MonitorWriteInteger(regsisters.eax);
			MonitorWrite("\n");

			MonitorWrite("ebx: ");
			MonitorWriteInteger(regsisters.ebx);
			MonitorWrite("\n");

			MonitorWrite("ecx: ");
			MonitorWriteInteger(regsisters.ecx);
			MonitorWrite("\n");

			MonitorWrite("edx: ");
			MonitorWriteInteger(regsisters.edx);
			MonitorWrite("\n");

			break;
		}
		}
	}
	else
	{
		MonitorWrite("Interupt: ");
		MonitorWriteInteger(interupt.interupt);
		MonitorWrite("\n");
	}

	asm volatile("movl %0, %%eax \n" :: "r" (result));
}
