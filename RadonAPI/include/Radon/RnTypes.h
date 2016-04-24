#ifndef RN_API_TYPES_H_INCLUDED
#define RN_API_TYPES_H_INCLUDED

#define RN_API
#define RN_HANDLE(name) typedef RnUInt32 * H##name

#include <stdint.h>

typedef int8_t RnInt8;
typedef uint8_t RnUInt8;

typedef int16_t RnInt16;
typedef uint16_t RnUInt16;

typedef int32_t RnInt32;
typedef uint32_t RnUInt32;

typedef int64_t RnInt64;
typedef uint64_t RnUInt64;

typedef RnInt32 RnResult;

#endif // RN_API_TYPES_H_INCLUDED
