/* cbreg.c - cbreg */

#include <xinu.h>

syscall cbreg(int(*fnp)())
{
	intmask mask;
	struct procent *prptr;
	
	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhascb) {
		restore(mask);
		return SYSERR;
	}
	prptr->fptr = fnp;
	prptr->prhascb = TRUE;
	restore(mask);
	return OK;
}
