#include <xinu.h>

syscall hascb1()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhascb1) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
