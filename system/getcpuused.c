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
	return prptr->prcputot;
}
