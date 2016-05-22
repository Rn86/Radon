#include <stdint.h>
#include <InteruptRequest.h>
#include <InteruptDescriptorTable.h>
#include <Assembly.h>
#include <Monitor.h>

extern void RnInteruptRequest_0();
extern void RnInteruptRequest_1();
extern void RnInteruptRequest_2();
extern void RnInteruptRequest_3();
extern void RnInteruptRequest_4();
extern void RnInteruptRequest_5();
extern void RnInteruptRequest_6();
extern void RnInteruptRequest_7();
extern void RnInteruptRequest_8();
extern void RnInteruptRequest_9();
extern void RnInteruptRequest_10();
extern void RnInteruptRequest_11();
extern void RnInteruptRequest_12();
extern void RnInteruptRequest_13();
extern void RnInteruptRequest_14();
extern void RnInteruptRequest_15();

static InteruptRequestHandler irqHandlers[16] = { 0 };

static RnResult RN_API RnInteruptRequestRemap();
static RnResult RN_API RnInteruptRequestSetGates();

RnResult RN_API RnInteruptRequestInitialize()
{
	RnInteruptRequestRemap();
	RnInteruptRequestSetGates();
	RnAssemblySTI();
	return 0;
}

RnResult RN_API RnInteruptRequestAcknowledge(uint32_t irq)
{
	if (irq >= 12)
    {
		RnAssemblyOUTB(0xA0, 0x20);
	}
	RnAssemblyOUTB(0x20, 0x20);
	return 0;
}

RnResult RN_API RnInteruptRequestAddHandler(uint32_t irq, InteruptRequestHandler handler)
{
	irqHandlers[irq] = handler;
	return 0;
}

RnResult RN_API RnInteruptRequestRemoveHandler(uint32_t irq)
{
	irqHandlers[irq] = 0;
	return 0;
}

static RnResult RN_API RnInteruptRequestRemap()
{
	RnAssemblyOUTB(0x20, 0x11);
	RnAssemblyOUTB(0xA0, 0x11);
	RnAssemblyOUTB(0x21, 0x20);
	RnAssemblyOUTB(0xA1, 0x28);
	RnAssemblyOUTB(0x21, 0x04);
	RnAssemblyOUTB(0xA1, 0x02);
	RnAssemblyOUTB(0x21, 0x01);
	RnAssemblyOUTB(0xA1, 0x01);
	RnAssemblyOUTB(0x21, 0x0);
	RnAssemblyOUTB(0xA1, 0x0);
	return 0;
}

static RnResult RN_API RnInteruptRequestSetGates()
{
	RnInteruptDescriptorTableSetGate(32, (uint32_t)RnInteruptRequest_0, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(33, (uint32_t)RnInteruptRequest_1, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(34, (uint32_t)RnInteruptRequest_2, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(35, (uint32_t)RnInteruptRequest_3, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(36, (uint32_t)RnInteruptRequest_4, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(37, (uint32_t)RnInteruptRequest_5, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(38, (uint32_t)RnInteruptRequest_6, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(39, (uint32_t)RnInteruptRequest_7, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(40, (uint32_t)RnInteruptRequest_8, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(41, (uint32_t)RnInteruptRequest_9, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(42, (uint32_t)RnInteruptRequest_10, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(43, (uint32_t)RnInteruptRequest_11, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(44, (uint32_t)RnInteruptRequest_12, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(45, (uint32_t)RnInteruptRequest_13, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(46, (uint32_t)RnInteruptRequest_14, 0x08, 0x8E);
	RnInteruptDescriptorTableSetGate(47, (uint32_t)RnInteruptRequest_15, 0x08, 0x8E);
	return 0;
}

void RN_API RnInteruptRequest(uint32_t ds, Registers registers, Interupt interupt)
{
    RnAssemblyCLI();
	if (interupt.interupt > 15 || !irqHandlers[interupt.interupt])
    {
		RnInteruptRequestAcknowledge(interupt.interupt);
	}
	else
	{
		irqHandlers[interupt.interupt]();
	}
	RnAssemblySTI();
}
