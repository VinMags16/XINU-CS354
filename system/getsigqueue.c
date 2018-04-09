#include <xinu.h>

syscall	getsigqueue()
{
	intmask mask;
	
	mask = disable();
	uint32 *queue = proctab[currpid].sigqueue;
	restore(mask);
	return queue;
}
