#include "Registers.h"
#include "SystemCall.h"
#include "Monitor.h"

void InteruptServiceRoutine(uint32_t ds, Registers regsisters, Interupt interupt)
{
	int32_t result = 1;

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
		switch ((SystemCall)regsisters.eax)
		{
		case rnscInitialize:
		{
			MonitorClear();
			break;
		}
		case rnscWrite:
		{
			result = MonitorWrite((char*)regsisters.ebx);
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