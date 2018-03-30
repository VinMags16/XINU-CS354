#include <xinu.h>
//#define DEBUG 0

void testproc()
{
	if (cbreg(&mrecv_cb) != OK) {
		kprintf("Callback registration failed!\n");
		return;
	}
	#ifdef DEBUG
		kprintf("Before sleep %d\n", currpid);
	#endif
	sleepms(1000);
	#ifdef DEBUG
		kprintf("After sleep %d\n", currpid);
	#endif
}
