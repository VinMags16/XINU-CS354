/* getcb.c - getcb */

#include <xinu.h>

syscall getcbrcv()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhasmsg || !prptr->prhascb) {
		restore(mask);
		return SYSERR;
	}
	int (*fnptr)() = prptr->fptr;
	restore(mask);
	return fnptr;
}

syscall getcbchl()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhascb1) {
		restore(mask);
		return SYSERR;
	}
	int (*fnptr)() = prptr->fptr1;
	restore(mask);
	return fnptr;
}

syscall getcbxtm()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (!prptr->prhascb2) {
		restore(mask);
		return SYSERR;
	}
	int (*fnptr)() = prptr->fptr2;
	restore(mask);
	return fnptr;	
}
