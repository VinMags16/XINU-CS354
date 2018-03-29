/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/
	struct 	procent *prptrsend;
	pid32	sendpid;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	
	if (prptr->rcpblkflag) {
		sendpid = dequeue(prptr->sendqueue);
		prptrsend = &proctab[sendpid];
		prptr->prmsg = prptrsend->sendblkmsg;
		prptrsend->sendblkflag = 0;
		ready(sendpid);
		if (isempty(prptr->sendqueue)) {
			prptr->rcpblkflag = 0;
		}
	} else {
		prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	}
	restore(mask);
	return msg;
}
