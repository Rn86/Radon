#include <stdio.h>

#include <RnSystemCall.h>
#include "../../Kernel/Tasking.h"

char * gets(char * str)
{
    int32_t length = 0;
    RnResult res = 0;
    for(;;)
    {
        RnSystemCallRead(str, &length);
        if (length) break;
        else RnTaskingSwitchTask();
    }
    return str;
}
