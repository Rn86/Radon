#ifndef RN_UNIT_TEST_H_INCLUDED
#define RN_UNIT_TEST_H_INCLUDED

#include <RnKernel.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef enum
{
    rnutcCount,
    rnutcList,
    rnutcRun,
    rnutcRunAll,
} RnUnitTestCode;

#define RN_TEST_GROUP_DECLARE(name) RnResult RN_API RnTestGroup##name(RnUnitTestCode code, char * input, uint32_t * pCount, uint32_t inCount, char ** parTests)

#define RN_TEST_GROUP(name) { #name, RnTestGroup##name }

#define RN_TEST_GROUP_BEGIN(name) \
RnResult RN_API RnTestGroup##name(RnUnitTestCode code, char * input, uint32_t * pCount, uint32_t inCount, char ** parTests)\
{\
    uint32_t error = 0;\
    char * group_name = #name;\
    char * test_name = NULL;\
    uint32_t count = 0;\
    uint32_t outCount = 0;\
    char * arTests = NULL;\
    if (code == rnutcList)\
    {\
        \
        if (!arTests) return -1;\
    }

#define RN_TEST_GROUP_END \
    if ((code == rnutcRunAll || code == rnutcRun) && test_name != NULL)\
    {\
        if (error) printf("%s::%s : FAIL\n", group_name, test_name);\
        else printf("%s::%s : PASS\n", group_name, test_name);\
        error = 0;\
    }\
    if (code == rnutcCount) *pCount = count;\
    if (code == rnutcList)\
    {\
        *pCount = outCount;\
        *parTests = arTests;\
    }\
    return 0;\
}

#define RN_TEST(name) \
    if ((code == rnutcRunAll || code == rnutcRun) && test_name != NULL)\
    {\
        if (error) printf("%s::%s : FAIL\n", group_name, test_name);\
        else printf("%s::%s : PASS\n", group_name, test_name);\
        error = 0;\
    }\
    test_name = #name;\
    if (code == rnutcCount) count ++;\
    if (code == rnutcList)\
    {\
        memcpy(&arTests[outCount], test_name, sizeof(#name));\
        outCount++;\
    }\
    if (code == rnutcRunAll || (code == rnutcRun && !strcmp(input, test_name)))


RnResult RN_API RnUnitTestGetCount(uint32_t * pCount);
RnResult RN_API RnUnitTestRunAll();

#endif // RN_UNIT_TEST_H_INCLUDED
