/* sigcbreg.c - sigcbreg */

#include <xinu.h>

syscall sigcbreg(uint16 ssig, int(*fnp)(), uint32 tmarg)
{
	intmask mask;
	struct procent *prptr;
	
	mask = disable();
	prptr = &proctab[currpid];
	if (ssig == XSIGRCV) {
		prptr->fptr = fnp;
		prptr->prhascb = TRUE;
	} else if (ssig == XSIGCHL) {
		prptr->fptr1 = fnp;
		prptr->prhascb1 = TRUE;
	} else if (ssig == XSIGXTM) {
		prptr->fptr2 = fnp;
		prptr->prhascb2 = TRUE;
		prptr->prwalltime = prptr->prstarttime + tmarg;
	} else {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
