/* xts_enqueue.c - xts_enqueue */

#include <xinu.h>

int xts_enqueue(pid32 pid, pri16 prio)
{
	/* Check if arguments are okay */
	if (isbadpid(pid) || prio < 0) {
		return -1;
	} else if (prio > SOLTS - 1) {
		prio = 59;
	}

	/* Insert process into ready list */
	enqueue(pid, xts_ready[prio].queue_head);
	xts_ready[prio].queue_tail = xts_ready[prio].queue_head;
	xts_ready[prio].status = 1;
	return 0;
}
