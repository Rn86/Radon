#include <Monitor.h>

static void outb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

static uint16_t *rnMonitorVideoMemory = (uint16_t *)0xB8000;
static uint8_t rnMonitorCursorX = 0;
static uint8_t rnMonitorCursorY = 0;

static RnKernelResult RN_KERNEL_API RnMonitorMoveCursor()
{
	uint16_t cursorLocation = rnMonitorCursorY * 80 + rnMonitorCursorX;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
	return 0;
}

static RnKernelResult RN_KERNEL_API RnMonitorScroll()
{
	uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attributeByte << 8);

    if(rnMonitorCursorY >= 25)
    {
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
			rnMonitorVideoMemory[i] = rnMonitorVideoMemory[i+80];
        }

        for (i = 24*80; i < 25*80; i++)
        {
			rnMonitorVideoMemory[i] = blank;
        }

		rnMonitorCursorY = 24;
    }
	return 0;
}

RnKernelResult RN_KERNEL_API RnMonitorPut(char c)
{
    uint8_t backColour = 0;
	uint8_t foreColour = 15;

	uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);

    uint16_t attribute = attributeByte << 8;
	uint16_t *location;

    if (c == 0x08 && rnMonitorCursorX)
    {
		rnMonitorCursorX--;
    }

    else if (c == 0x09)
    {
		rnMonitorCursorX = (rnMonitorCursorX + 8) & ~(8-1);
    }

    else if (c == '\r')
    {
		rnMonitorCursorX = 0;
    }

    else if (c == '\n')
    {
		rnMonitorCursorX = 0;
		rnMonitorCursorY++;
    }

    else if(c >= ' ')
    {
        location = rnMonitorVideoMemory + (rnMonitorCursorY * 80 + rnMonitorCursorX);
        *location = c | attribute;
		rnMonitorCursorX++;
    }

    if (rnMonitorCursorX >= 80)
    {
		rnMonitorCursorX = 0;
		rnMonitorCursorY++;
    }

    RnMonitorScroll();
	RnMonitorMoveCursor();
	return 0;
}

RnKernelResult RN_KERNEL_API RnMonitorInitialize()
{
    uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 8);

    int32_t i = 0;
    for (i = 0; i < 80*25; i++)
    {
		rnMonitorVideoMemory[i] = blank;
    }

	rnMonitorCursorX = 0;
	rnMonitorCursorY = 0;
    RnMonitorMoveCursor();
	return 0;
}

RnKernelResult RN_KERNEL_API RnMonitorWrite(char * szValue)
{
	int32_t i = 0;
	while(szValue[i])
	{
		RnMonitorPut(szValue[i++]);
	}
	return 0;
}

RnKernelResult RN_KERNEL_API RnMonitorWriteLength(char * szValue, int32_t length)
{
	int32_t i = 0;
	for (i = 0; i < length; i++)
	{
		RnMonitorPut(szValue[i]);
	}
	return 0;
}

RnKernelResult RN_KERNEL_API RnMonitorWriteInteger(uint32_t value)
{
	if (value == 0)
	{
		RnMonitorPut('0');
		return 0;
	}

	int32_t acc = value;
	char c[32];
	int i = 0;
	while (acc > 0)
	{
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while (i >= 0)
	{
		c2[i--] = c[j++];
	}
	RnMonitorWrite(c2);
	return 0;
}
