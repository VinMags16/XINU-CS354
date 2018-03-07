/* iobound.c - iobound */

#include <xinu.h>

#define UP1 10
#define UP2 10

void iobound()
{
	for (int i = 0; i < UP1; i++) {
		for (int j = 0; j < UP2; j++) {
			sleepms(40);
			kprintf("Pid = %d\nCount = %d\nPrcputot = %d\n\n", currpid, i, getcputot(currpid));
		}
	}
	kprintf("Process end stats for pid %d\nPrcputot = %d\nPrprio = %d\nPreempt = %d\n\n", currpid, getcputot(currpid), proctab[currpid].prprio, preempt);
}
