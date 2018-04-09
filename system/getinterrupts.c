#include <xinu.h>

syscall	getinterrupts()
{
	intmask	mask;

	mask = disable();
	int *interrupts = (int*) proctab[currpid].sigqueue;
	restore(mask);
	return interrupts;
}
