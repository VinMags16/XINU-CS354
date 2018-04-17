/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	struct procent *parent = &proctab[prptr->prparent];
	for (int i = 0; i < 3; i++) {
		if (parent->sigqueue[i] == XSIGCHL) {
			break;
		} else if (parent->sigqueue[i] == 0) {
			parent->sigqueue[i] = XSIGCHL;
		}
	}
	parent->numChildren--;
	if (parent->deadchild == -1) {
		parent->deadchild = pid;
	}
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	memclear();
	freestk(prptr->prstkbase, prptr->prstklen);
	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		if (parent->prstate == PR_CHLDWAIT) {
			ready(prptr->prparent);
		}
		resched();
	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}
	restore(mask);
	cbhandler();
	return OK;
}
