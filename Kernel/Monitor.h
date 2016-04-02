#ifndef RN_KERNEL_MONITOR_H_INCLUDED
#define RN_KERNEL_MONITOR_H_INCLUDED

#include <stdint.h>

void MonitorClear();
void MonitorWrite(char * szValue);
void MonitorWriteInteger(uint32_t value);

#endif //!MONITOR_H
