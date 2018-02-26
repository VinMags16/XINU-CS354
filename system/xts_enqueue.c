/* xts_enqueue.c - xts_enqueue */

#include <xinu.h>

int xts_enqueue(pid32 pid, pri16 prio)
{
	/* Check if arguments are okay */
	if (isbadpid(pid) || prio < 0 || prio > 59) {
		return -1;
	}

	/* Check if there isn't a list yet in the priority spot - create one if there isn't */
	struct xts_multifb level = xts_read[prio];
	if (!level.status) {
		
		level.queue_head = 0;
		level.queue_tail = 0;
		level.status = 1;
		return 0;
	}

	/* There is a list, enqueue in it */


	return -1;
}
