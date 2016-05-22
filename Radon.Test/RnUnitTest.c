#include <RnUnitTest.h>
#include <RnKernel.h>

RN_TEST_GROUP_DECLARE(GroupExample);

struct
{
    char * group_name;
    RnResult (RN_API * test_group)(RnUnitTestCode code, char * input, uint32_t * pCount, uint32_t inCount, char ** parTests);
} rnUnitTestGroups[] =
{
    RN_TEST_GROUP(GroupExample),
};

RnResult RN_API RnUnitTestGetCount(uint32_t * pCount)
{
    if (!pCount) return -1;
    *pCount = sizeof(rnUnitTestGroups) / sizeof(rnUnitTestGroups[0]);
    return 0;
}

RnResult RN_API RnUnitTestRunAll()
{
    uint32_t i = 0;
    uint32_t count = 0;

    RnUnitTestGetCount(&count);

    for (i = 0; i < count; i++)
    {
        rnUnitTestGroups[i].test_group(rnutcRunAll, NULL, NULL, 0, NULL);
    }
    return 0;
}
