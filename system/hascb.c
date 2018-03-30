#include <xinu.h>

syscall hascb()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhascb || !prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
