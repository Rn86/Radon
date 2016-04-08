#ifndef RN_KERNEL_MONITOR_H_INCLUDED
#define RN_KERNEL_MONITOR_H_INCLUDED

#include <stdint.h>

void MonitorClear();
int32_t MonitorWrite(char * szValue);
uint32_t MonitorWriteLength(char * szValue, uint32_t length);
void MonitorWriteInteger(uint32_t value);

#endif //!RN_KERNEL_MONITOR_H_INCLUDED
