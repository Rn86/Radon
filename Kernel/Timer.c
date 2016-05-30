#include <Timer.h>
#include <InteruptRequest.h>
#include <Assembly.h>

#include <Tasking.h>

#include <Monitor.h>

#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CHANNEL1      0x41  //PIT Channels 1's Data Register Port, we wont be using this here
#define PIT_CHANNEL2      0x42  //PIT Channels 2's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port

#define PIT_MASK 0xFF
#define PIT_SCALE 1193180
#define PIT_SET 0x36

static RnResult RN_API RnTimerSetFrequency(uint32_t hz);
static RnResult RN_API RnTimerIRQHandler();

RnResult RN_API RnTimerInitialize()
{
	RnInteruptRequestAddHandler(0, RnTimerIRQHandler);
	RnTimerSetFrequency(100);
	return 0;
}

static RnResult RN_API RnTimerSetFrequency(uint32_t hz)
{
	int divisor = PIT_SCALE / hz;
	RnAssemblyOUTB(PIT_CMDREG, PIT_SET);
	RnAssemblyOUTB(PIT_CHANNEL0, divisor & PIT_MASK);
	RnAssemblyOUTB(PIT_CHANNEL0, (divisor >> 8) & PIT_MASK);
	return 0;
}

static RnResult RN_API RnTimerIRQHandler()
{
    //RnMonitorWrite("timer\n");

    //
    RnInteruptRequestAcknowledge(0);
    //RnTaskingSwitchTask();
    //RnInteruptRequestAcknowledge(0);
	return 0;
}
