#include <xinu.h>

syscall	sigcbunreg(uint16 ssig)
{
	intmask	mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (ssig == XSIGRCV) {
		if (!prptr->prhascb) {
			restore(mask);
			return SYSERR;
		}
		prptr->fptr = NULL;
		prptr->prhascb = FALSE;
	} else if (ssig == XSIGCHL) {
		if (!prptr->prhascb1) {
			restore(mask);
			return SYSERR;
		}
		prptr->fptr1 = NULL;
		prptr->prhascb1 = FALSE;

	} else if (ssig == XSIGXTM) {
		if (!prptr->prhascb2) {
			restore(mask);
			return SYSERR;
		}
		prptr->fptr2 = NULL;
		prptr->prhascb2 = FALSE;
	} else {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
