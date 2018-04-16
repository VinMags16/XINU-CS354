#include <xinu.h>

syscall	childwait()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->numChildren <= 0 && prptr->deadchild == -1) {
		restore(mask);
		return SYSERR;
	} else if (prptr->deadchild == -1) {
		prptr->prstate = PR_CHLDWAIT;
		resched();
		pid32 pid = prptr->deadchild;
		prptr->deadchild = -1;
		restore(mask);
		cbhandler();
		return pid;
	} else {
		pid32 pid = prptr->deadchild;
		prptr->deadchild = -1;
		restore(mask);
		cbhandler();
		return pid;
	}
}
