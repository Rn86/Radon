#include <Keyboard.h>
#include <Monitor.h>
#include <InteruptRequest.h>
#include <Assembly.h>

#include <string.h>

#define RN_KEYBOARD_BUFFER_LENGTH 256

static uint32_t rnCounter = 0;
static char rnBuffer[RN_KEYBOARD_BUFFER_LENGTH] = { 0 };

static char rnKeyboardMap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static RnResult RN_API RnKeyboardIRQHandler();

RnResult RN_API RnKeyboardInitialize()
{
    RnInteruptRequestAddHandler(1, RnKeyboardIRQHandler);
    return 0;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for ( size_t i = 0; i < size; i++ )
		dst[i] = src[i];
	return dstptr;
}

RnResult RN_API RnKeyboardRead(char * buffer, uint32_t * pLength)
{
    uint32_t found = 0;
    uint32_t length = 0;

    for (length = 0; length < rnCounter; length++)
    {
        if (rnBuffer[length] == '\n')
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        memcpy(buffer, rnBuffer, length);
        buffer[length] = '\0';
        rnCounter = 0;
        *pLength = length + 1;
        return length;
    }

    return 0;
}

static RnResult RN_API RnKeyboardIRQHandler()
{
	uint8_t scancode = 0;

    scancode = RnAssemblyINB(0x60);

    if (!(scancode & 0x80))
    {
        rnBuffer[rnCounter++] = rnKeyboardMap[scancode];
        RnMonitorPut(rnKeyboardMap[scancode]);
    }

	RnInteruptRequestAcknowledge(1);
	return 0;
}
