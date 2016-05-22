#ifndef RN_KERNEL_MONITOR_H_INCLUDED
#define RN_KERNEL_MONITOR_H_INCLUDED

#include <RnKernel.h>

RnResult RN_API RnMonitorInitialize();
RnResult RN_API RnMonitorPut(char c);
RnResult RN_API RnMonitorWrite(char * szValue);
RnResult RN_API RnMonitorWriteLength(char * szValue, int32_t length);
RnResult RN_API RnMonitorWriteInteger(uint32_t value);

#endif //!RN_KERNEL_MONITOR_H_INCLUDED
