#ifndef RN_MEMORY_H_INCLUDED
#define RN_MEMORY_H_INCLUDED

#include <RnKernel.h>

RnResult RN_API RnMemoryInitialize();

RnResult RN_API RnPagingInitialize();

// TODO: make Rn memory api

void * malloc(size_t size);
void free(void * mem);

#endif //!RN_MEMORY_H_INCLUDED
