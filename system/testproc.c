//#define DEBUG 0
#include <xinu.h>

void testproc()
{
	if (sigcbreg(XSIGRCV, &mrecv_cb, NULL) != OK) {
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
