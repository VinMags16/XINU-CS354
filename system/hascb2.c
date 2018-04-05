#include <xinu.h>

syscall hascb2()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhascb2) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
