#include <xinu.h>

syscall	handlesigs()
{
	intmask	mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->sigqueue[0].ssig == XSIGRCV && prptr->prhascb) {
		int(*fnptr)() = prptr->fptr;
		(*fnptr)();
		prptr->sigqueue[0].ssig = NULL;
		prptr->prhascb = FALSE;
	}
	if (prptr->sigqueue[1].ssig == XSIGCHL && prptr->prhascb1) {
		int(*fnptr)() = prptr->fptr1;
		(*fnptr)();
		prptr->sigqueue[1].ssig = NULL;
		prptr->prhascb1 = FALSE;
	}
	if (prptr->sigqueue[2].ssig == XSIGXTM  && prptr->prhascb2) {		
		int(*fnptr)() = prptr->fptr2;
		(*fnptr)();
		prptr->sigqueue[2].ssig = NULL;
		prptr->prhascb2 = FALSE;
	}
	restore(mask);
	return OK;
}
