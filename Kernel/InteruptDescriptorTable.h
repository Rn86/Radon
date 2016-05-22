#ifndef INTERUPT_DESCRIPTOR_TABLE_H_INCLUDED
#define INTERUPT_DESCRIPTOR_TABLE_H_INCLUDED

#include <RnKernel.h>

RnResult RN_API RnInteruptDescriptorTableInitialize();
RnResult RN_API RnInteruptDescriptorTableSetGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif //!INTERUPT_DESCRIPTOR_TABLE_H_INCLUDED
