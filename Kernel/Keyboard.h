#ifndef RN_KERNEL_KEYBOARD_H_INCLUDED
#define RN_KERNEL_KEYBOARD_H_INCLUDED

#include <RnKernel.h>

RnResult RN_API RnKeyboardInitialize();

RnResult RN_API RnKeyboardRead(char * buffer, uint32_t * pLength);

#endif // RN_KERNEL_KEYBOARD_H_INCLUDED
