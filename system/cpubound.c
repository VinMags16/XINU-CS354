/* cpubound.c - cpubound */

#include <xinu.h>

#define UP1  20 
#define UP2 10

void cpubound()
{
	for (int i = 0; i < UP1; i++) {
		for (int j = 0; j < UP2; j++) {
			bool8 val = TRUE || FALSE;
			kprintf("Pid = %d\nCount = %d\nPrcputot = %d\n\n", currpid, i, proctab[currpid].prcputot);
		}
	}
	kprintf("Process end stats for pid %d\nPrcputot = %d\nPrprio = %d\nPreempt = %d\n\n", currpid, proctab[currpid].prcputot, proctab[currpid].prprio, preempt);
}
