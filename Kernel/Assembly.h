#ifndef RN_KERNEL_ASSEMBLY_H_INCLUDED
#define RN_KERNEL_ASSEMBLY_H_INCLUDED

inline void RnAssemblySTI()
{
    asm volatile("sti");
}

inline void RnAssemblyCLI()
{
    asm volatile("cli");
}

inline void RnAssemblyHLT()
{
    asm volatile("hlt");
}

inline void RnAssemblyOUTB(uint16_t port, uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

inline uint8_t RnAssemblyINB(uint16_t port)
{
   uint8_t ret = 0;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}

#endif // RN_KERNEL_ASSEMBLY_H_INCLUDED
