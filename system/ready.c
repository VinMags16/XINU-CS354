/* ready.c - ready */

#include <xinu.h>
#define DEBUG 0

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	/* Vincent Maggioli */
	/* Insert into multi level feedback queue */

	#ifdef DEBUG
		kprintf("Enqueueing process %s\n", prptr->prname);
	#endif	
	xts_enqueue(pid, prptr->prprio);

	/* End changes */

	resched();

	return OK;
}
