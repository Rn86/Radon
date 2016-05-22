#include <SystemCall.h>
#include <Registers.h>
#include <Monitor.h>
#include <Keyboard.h>
#include <InteruptDescriptorTable.h>

extern void RnInteruptServiceRoutine_0();
extern void RnInteruptServiceRoutine_1();
extern void RnInteruptServiceRoutine_2();
extern void RnInteruptServiceRoutine_3();
extern void RnInteruptServiceRoutine_4();
extern void RnInteruptServiceRoutine_5();
extern void RnInteruptServiceRoutine_6();
extern void RnInteruptServiceRoutine_7();
extern void RnInteruptServiceRoutine_8();
extern void RnInteruptServiceRoutine_9();
extern void RnInteruptServiceRoutine_10();
extern void RnInteruptServiceRoutine_11();
extern void RnInteruptServiceRoutine_12();
extern void RnInteruptServiceRoutine_13();
extern void RnInteruptServiceRoutine_14();
extern void RnInteruptServiceRoutine_15();
extern void RnInteruptServiceRoutine_16();
extern void RnInteruptServiceRoutine_17();
extern void RnInteruptServiceRoutine_18();
extern void RnInteruptServiceRoutine_19();
extern void RnInteruptServiceRoutine_20();
extern void RnInteruptServiceRoutine_21();
extern void RnInteruptServiceRoutine_22();
extern void RnInteruptServiceRoutine_23();
extern void RnInteruptServiceRoutine_24();
extern void RnInteruptServiceRoutine_25();
extern void RnInteruptServiceRoutine_26();
extern void RnInteruptServiceRoutine_27();
extern void RnInteruptServiceRoutine_28();
extern void RnInteruptServiceRoutine_29();
extern void RnInteruptServiceRoutine_30();
extern void RnInteruptServiceRoutine_31();
extern void RnInteruptServiceRoutine_127();

RnResult RN_API RnInteruptServiceRoutineInitialize()
{
    RnInteruptDescriptorTableSetGate(0,   (uint32_t)RnInteruptServiceRoutine_0,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(1,   (uint32_t)RnInteruptServiceRoutine_1,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(2,   (uint32_t)RnInteruptServiceRoutine_2,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(3,   (uint32_t)RnInteruptServiceRoutine_3,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(4,   (uint32_t)RnInteruptServiceRoutine_4,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(5,   (uint32_t)RnInteruptServiceRoutine_5,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(6,   (uint32_t)RnInteruptServiceRoutine_6,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(7,   (uint32_t)RnInteruptServiceRoutine_7,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(8,   (uint32_t)RnInteruptServiceRoutine_8,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(9,   (uint32_t)RnInteruptServiceRoutine_9,   0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(10,  (uint32_t)RnInteruptServiceRoutine_10,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(11,  (uint32_t)RnInteruptServiceRoutine_11,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(12,  (uint32_t)RnInteruptServiceRoutine_12,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(13,  (uint32_t)RnInteruptServiceRoutine_13,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(14,  (uint32_t)RnInteruptServiceRoutine_14,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(15,  (uint32_t)RnInteruptServiceRoutine_15,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(16,  (uint32_t)RnInteruptServiceRoutine_16,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(17,  (uint32_t)RnInteruptServiceRoutine_17,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(18,  (uint32_t)RnInteruptServiceRoutine_18,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(19,  (uint32_t)RnInteruptServiceRoutine_18,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(20,  (uint32_t)RnInteruptServiceRoutine_20,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(21,  (uint32_t)RnInteruptServiceRoutine_21,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(22,  (uint32_t)RnInteruptServiceRoutine_22,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(23,  (uint32_t)RnInteruptServiceRoutine_23,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(24,  (uint32_t)RnInteruptServiceRoutine_24,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(25,  (uint32_t)RnInteruptServiceRoutine_25,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(26,  (uint32_t)RnInteruptServiceRoutine_26,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(27,  (uint32_t)RnInteruptServiceRoutine_27,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(28,  (uint32_t)RnInteruptServiceRoutine_28,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(29,  (uint32_t)RnInteruptServiceRoutine_29,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(30,  (uint32_t)RnInteruptServiceRoutine_30,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(31,  (uint32_t)RnInteruptServiceRoutine_31,  0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(127, (uint32_t)RnInteruptServiceRoutine_127, 0x08, 0x8E);

	return 0;
}

void RnInteruptServiceRoutine(uint32_t ds, Registers registers, Interupt interupt)
{
	RnResult result = 0;

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
			break;
		}
		case rnscWrite:
		{
			result = RnMonitorWriteLength((char*)registers.ecx, (int32_t)registers.ebx);
			break;
		}
		case rnscRead:
        {
            result = RnKeyboardRead((char*)registers.ecx, (uint32_t*)registers.ebx);
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
