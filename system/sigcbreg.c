/* sigcbreg.c - sigcbreg */

#include <xinu.h>

syscall sigcbreg(uint16 ssig, int(*fnp)(), uint32 tmarg)
{
	intmask mask;
	struct procent *prptr;
	
	mask = disable();
	prptr = &proctab[currpid];
	prptr->fptr = fnp;
	prptr->prhascb = TRUE;
	restore(mask);
	return OK;
}
