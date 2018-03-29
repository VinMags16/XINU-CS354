/* getcb.c - getcb */

#include <xinu.h>

syscall getcb()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhasmsg || !prptr->prhascb) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
