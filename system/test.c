/* test.c - test */

#include <xinu.h>
#define DEBUG 0

void test()
{
	if (cbreg(&mrecv_cb) != OK) {
		kprintf("cb registration failed!\n");
		return;
	}
	#ifdef DEBUG
		kprintf("Before sleep\n");
	#endif
	sleepms(1000);
	#ifdef DEBUG
		kprintf("After sleep\n");
	#endif
}
