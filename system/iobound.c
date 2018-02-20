/* iobound.c - iobound */

#include <xinu.h>

#define UP1 5
#define UP2 30

void iobound()
{
	for (int i = 0; i < UP1; i++) {
		for (int j = 0; j < UP2; j++) {
			sleepms(30);
			kprintf("Pid = %d\nCount = %d\nPrcputot = %d\n\n", currpid, i, proctab[currpid].prcputot);
		}
	}
	kprintf("Process end stats for pid %d\nPrcputot = %d\nPrprio = %d\nPreempt = %d\n\n", currpid, proctab[currpid].prcputot, proctab[currpid].prprio, preempt);
}
