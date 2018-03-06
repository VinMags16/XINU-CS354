/* resched.c - resched, resched_cntl */

#include <xinu.h>

//#define DEBUG 0

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
	#ifdef DEBUG
		kprintf("Current preempt: %d\n", preempt);
	#endif
	pri16 currPri = ptold->prprio;
	if (preempt <= 0 && currpid != 0) {
		/* CPU Bound */
		ptold->prprio = xts_conf[ptold->prprio].xts_tqexp;	
		kprintf("CPU Bound: %s\nOld: %d\tNew: %d\n\n", ptold->prname, currPri, ptold->prprio);	
	} else if (currpid != 0) {
		/* IO Bound */
		kprintf("IO Bound: %s\n", ptold->prname);
		ptold->prprio = xts_conf[ptold->prprio].xts_slpret;
	}
	
	#ifdef DEBUG
		kprintf("Process %s new prio: %d\n", ptold->prname, ptold->prprio);
	#endif
	
	/* End changes */

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		/* Vincent Maggioli */
		/* Modify readylist check to use xts_priochk  */
		#ifdef DEBUG
			kprintf("xts_priochk(): %d\n", xts_priochk());
		#endif
		kprintf("prprio = %d\txts_priochk() = %d\n", ptold->prprio, xts_priochk());
		if (ptold->prprio > xts_priochk()) {
			/* Set proper new preempt based on new prio */
			preempt = xts_conf[ptold->prprio].xts_quantum;
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;

		/* Enqueue process into multi-level fq */	

		xts_enqueue(currpid, ptold->prprio);
		#ifdef DEBUG
			kprintf("%d\n", queuetab[xts_ready[ptold->prprio].queue_tail].qprev);
		#endif
		
	}

	/* Force context switch to highest priority ready process */

	currpid = xts_dequeue();
	ptnew = &proctab[currpid];
	
	/* Adds cpu usage to process getting swapped out */
	/* Sets beginning time in ms for new process */
	
	uint32 consumedTime = clkmilli - ptold->prctxswbeg;
	ptold->prcputot += consumedTime;
	ptnew->prctxswbeg = clkmilli;

	/* Set preempt based on new prio */
	
	preempt = xts_conf[ptnew->prprio].xts_quantum;
	
	/* Print values on context switch if debugging */
	#ifdef DEBUG
		if (currpid != 0) {
			kprintf("Process %s\nCPU session time: %d\nCPU total time: %d\n\n", ptold->prname, consumedTime, ptold->prcputot);
		}
	#endif

	/* End changes */

	ptnew->prstate = PR_CURR;
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
