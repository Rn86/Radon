#ifndef RN_KERNEL_MONITOR_H_INCLUDED
#define RN_KERNEL_MONITOR_H_INCLUDED

#include "Kernel.h"

RnKernelResult RN_KERNEL_API RnMonitorInitialize();
RnKernelResult RN_KERNEL_API RnMonitorWrite(char * szValue);
RnKernelResult RN_KERNEL_API RnMonitorWriteLength(char * szValue, int32_t length);
RnKernelResult RN_KERNEL_API RnMonitorWriteInteger(uint32_t value);

#endif //!RN_KERNEL_MONITOR_H_INCLUDED
