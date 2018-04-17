#include <xinu.h>

syscall clearsigrcv()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGRCV) {
			prptr->sigqueue[i] = 0;
		}
	}
	prptr->prhasmsg = FALSE;
	prptr->prmsg = NULL;
	restore(mask);
	return OK;
}

syscall clearsigchl()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGCHL) {
			prptr->sigqueue[i] = 0;
		}
	}
	prptr->deadchild = -1;
	restore(mask);
	return OK;
}

syscall clearsigxtm()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	for (int i = 0; i < 3; i++) {
		if (prptr->sigqueue[i] == XSIGXTM) {
			prptr->sigqueue[i] = 0;
		}
	}
	restore(mask);
	return OK;
}
