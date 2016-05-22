#include <RnKernel.h>

#include <RnUnitTest.h>

#include <stdio.h>

RnResult RN_API RnKernelMain()
{
	//RnSystemCallWrite("Hello World\n", 12);

    //RnSystemCallWrite("Switching to otherTask... \n", 20);
    //Preempt();
    //RnSystemCallWrite("Returned to mainTask!\n", 20);

    RnUnitTestRunAll();

	while (1);

	return 0;
}
