#ifndef RN_SYSTEM_CALL_INCLUDED_H
#define RN_SYSTEM_CALL_INCLUDED_H

typedef enum
{
    rnscInitialize = 0,
    rnscWrite = 1,
    rnscAllocate = 2,
    rnscDeallocate = 3,
} RnSystemCall;

#endif //!RN_SYSTEM_CALL_INCLUDED_H
