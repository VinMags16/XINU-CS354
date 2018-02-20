/* getcpuused.c - getcputot */

#include <xinu.h>

syscall getcputot(pid32 pid)
{
	struct	procent	*prptr;		/* pointer to process  */
	intmask	mask;			/* interrupt mask	*/

	/* Disable interrupts and check if pid is valid */
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	/* Get process and return its cpu total */
	prptr = &proctab[pid];
	restore(mask);
	if (prptr->prstate == PR_CURR) {
		return prptr->prcputot + (clkmilli - prptr->prctxswbeg);
	}
	return prptr->prcputot;
}
