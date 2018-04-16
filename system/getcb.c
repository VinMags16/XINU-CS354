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
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGRCV) {
			prptr->sigqueue[i] = 0;
			break;
		}
	}
	restore(mask);
	return fnptr;
}

syscall getcbchl()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	kprintf("%d\n", currpid);
	if (!prptr->prhascb1) {
		restore(mask);
		return SYSERR;
	}
	int (*fnptr)() = prptr->fptr1;
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGCHL) {
			prptr->sigqueue[i] = 0;
			break;
		}
	}
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
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGXTM) {
			prptr->sigqueue[i] = 0;
			break;
		}
	}
	restore(mask);
	return fnptr;	
}
