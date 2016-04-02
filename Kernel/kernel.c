#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
#include "isr.h"
#include "DescriptorTables.h"
#include "Monitor.h"
#include "SystemCall.h"

void isr_handler(registers_t regs)
{
	if (regs.err_code)
	{
		MonitorWrite("Error interupt: ");
		MonitorWriteInteger(regs.int_no);
		MonitorWrite("\n");

		MonitorWrite("Error code: ");
		MonitorWriteInteger(regs.err_code);
		MonitorWrite("\n");
	}
	else if (regs.int_no == 127)
	{
		switch ((SystemCall)regs.eax)
		{
		case rnscWrite:
		{
			MonitorWrite((char*)regs.ebx);
			break;
		}
		default:
		{
			MonitorWrite("Unknown system call: ");
			MonitorWriteInteger(regs.int_no);
			MonitorWrite("\n");

			MonitorWrite("eax: ");
			MonitorWriteInteger(regs.eax);
			MonitorWrite("\n");

			MonitorWrite("ebx: ");
			MonitorWriteInteger(regs.ebx);
			MonitorWrite("\n");

			MonitorWrite("ecx: ");
			MonitorWriteInteger(regs.ecx);
			MonitorWrite("\n");

			MonitorWrite("edx: ");
			MonitorWriteInteger(regs.edx);
			MonitorWrite("\n");

			break;
		}
		}
	}
	while (1){}
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
	// Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    MonitorClear();
    // Write out a sample string
    Write("Hello, world!\n");
}