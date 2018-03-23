/* xts_dequeue.c - xts_dequeue */

#include <xinu.h>

pid32 xts_dequeue()
{
	pri16 prio = xts_priochk();
	if (xts_ready[prio].status) {
		pri16 element = dequeue(xts_ready[prio].queue_head);
		if (isempty(xts_ready[prio].queue_head)) {
			xts_ready[prio].status = 0;
		}
		return element;
	}
	return 0;
}
