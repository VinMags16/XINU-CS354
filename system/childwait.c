#include <xinu.h>

syscall	childwait()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->numChildren <= 0 && prptr->deadchild == -1) {
		return SYSERR;
	} else if (prptr->deadchild == -1) {
		kprintf("Blocking\n");
		prptr->prstate = PR_CHLDWAIT;
		resched();
		pid32 pid = prptr->deadchild;
		prptr->deadchild = -1;
		restore(mask);
		cbhandler();
		return pid;
	} else {
		kprintf("Immediate\n");
		pid32 pid = prptr->deadchild;
		prptr->deadchild = -1;
		for (int i = 0; i < 3; i++) {
			if (prptr->sigqueue[i] == XSIGCHL) {
				prptr->sigqueue[i] = 0;
				break;
			}
		}
		restore(mask);
		return pid;
	}
}
