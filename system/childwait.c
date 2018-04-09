#include <xinu.h>

syscall	childwait()
{
	intmask mask;

	mask = disable();
	if (proctab[currpid].numChildren <= 0) {
		return SYSERR;
	}
	proctab[currpid].prstate = PR_CHLDWAIT;
	resched();
	pid32 pid = proctab[currpid].deadchild;
	kprintf("%d\n", currpid);
	restore(mask);
	cbhandler();
	return pid;
}
