#include <xinu.h>

syscall	childwait()
{
	intmask mask;

	mask = disable();
	if (proctab[currpid].numChildren <= 0) {
		return SYSERR;
	}
	proctab[currpid].prstate = PR_CHLDWAIT;
	pid32 pid = currpid;
	resched();
	restore(mask);
	cbhandler();
	return pid;
}
