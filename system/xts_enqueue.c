/* xts_enqueue.c - xts_enqueue */

#include <xinu.h>

int xts_enqueue(pid32 pid, pri16 prio)
{	

	/* Check if arguments are okay */
	if (isbadpid(pid) || prio < 0 || prio > SOLTS-1) {
		return -1;
	}

	/* Insert process into ready list */
	struct xts_multifb level = xts_ready[prio];
	enqueue(pid, level.queue_head);
	level.status = 1;
	return 0;
}
