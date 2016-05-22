#ifndef RN_TYPES_H_INCLUDED
#define RN_TYPES_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t RnUInt8;
typedef int8_t RnInt8;
typedef uint16_t RnUInt16;
typedef int16_t RnInt16;
typedef uint32_t RnUInt32;
typedef int32_t RnInt32;
typedef uint64_t RnUInt64;
typedef int64_t RnInt64;

typedef char RnChar;

typedef bool RnBool;

#ifdef RN_x64
    typedef RnUInt64 RnUInt;
    typedef RnInt64 RnInt;
#else
    typedef RnUInt32 RnUInt;
    typedef RnInt32 RnInt;
#endif

typedef RnInt RnResult;

#define RN_API

#define RN_OK 0

#define RN_FAILED(result) \
    result < RN_OK

#define RN_SUCCEEDED(result) \
    result >= RN_OK

#define RN_HANDLE(name) typedef RnUInt * H##name;

#define RN_TRY \
    RnResult RnFunctionResult = RN_OK;\
    RnBool RnFunctionFinally = false;\

#define RN_END \
    RN_FINALLY \
    RN_E

#define RN_FINALLY \
    RnFunctionFinallyLabel: \
    RnFunctionFinally = true;

#define RN_E \
    return RnFunctionResult;

#define RN_CHECK(result) \
    if (RN_FAILED(result)) \
    { \
        RnFunctionResult = result; \
        if (!RnFunctionFinally) \
            goto RnFunctionFinallyLabel;\
    }

#endif // RN_TYPES_H_INCLUDED
