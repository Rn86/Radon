#ifndef RN_INTERUPT_REQUEST_H_INCLUDED
#define RN_INTERUPT_REQUEST_H_INCLUDED

#include <RnKernel.h>
#include <Registers.h>

typedef RnResult (RN_API * InteruptRequestHandler) ();

RnResult RN_API RnInteruptRequestInitialize();
RnResult RN_API RnInteruptRequestAcknowledge(uint32_t irq);
RnResult RN_API RnInteruptRequestAddHandler(uint32_t irq, InteruptRequestHandler handler);
RnResult RN_API RnInteruptRequestRemoveHandler(uint32_t irq);

#endif // RN_INTERUPT_REQUEST_H_INCLUDED
