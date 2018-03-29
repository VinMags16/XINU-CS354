/* sendblk.c - sendblk */

#include <xinu.h>

syscall sendblk(
	pid32	pid,
	umsg32	msg
)
{
	intmask mask;
	struct procent *prptr;
	struct procent *prptrcurr;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	
	prptr = &proctab[pid];
	if (prptr->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	prptrcurr = &proctab[currpid];
	if (prptr->prhasmsg) {
		prptrcurr->sendblkflag = 1;
		prptrcurr->sendblkmsg = msg;
		prptrcurr->sendblkrcp = pid;
		prptr->rcpblkflag = 1;
		enqueue(currpid, prptr->sendqueue);
		prptrcurr->prstate = PR_SNDBLK;
		resched();
		return OK;
	}

	prptr->prmsg = msg;
	prptr->prhasmsg = 1;
	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);
	return OK;
}
