/* resched.c - resched, resched_cntl */

#include <xinu.h>

#define DEBUG 0

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	
	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	/* Vincent Maggioli */
	/* Set new priority based on I/O or CPU bound */

	pri16 currPrio = ptold->prprio;
	if (preempt <= 0) {
		/* CPU Bound */
		ptold->prprio = xts_conf[currPrio].xts_tqexp;	
	} else {
		/* IO Bound */
		ptold->prprio = xts_conf[currPrio].xts_slpret;
	}
	
	/* End changes */

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		/* Vincent Maggioli */
		/* Modify readylist check to use xts_priochk  */
		if (ptold->prprio > xts_priochk()) {
			/* Set proper new preempt based on new prio */
			preempt = xts_conf[ptold->prprio].xts_quantum;
			return;
		}

		/* End changes */

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;

		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	
	/* Vincent Maggioli 2/13 */
	/* Adds cpu usage to process getting swapped out */
	/* Sets beginning time in ms for new process */
	
	uint32 consumedTime = clkmilli - ptold->prctxswbeg;
	ptold->prcputot += consumedTime;
	ptnew->prctxswbeg = clkmilli;

	/* Set new preempt based on new prio */
	
	preempt = xts_conf[ptnew->prprio].xts_quantum;
	
	/* Print values on context switch if debugging */
	#ifdef DEBUG
		kprintf("Process %s\nCPU session time: %d\nCPU total time: %d\n\n", ptold->prname, consumedTime, ptold->prcputot);
	#endif

	/* end changes */

	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
