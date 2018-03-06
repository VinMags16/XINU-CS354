/* xts_dequeue.c - xts_dequeue */

#include <xinu.h>

pid32 xts_dequeue()
{
	for (int i = SOLTS-1; i >= 0; i--) {
		if (xts_ready[i].status) {
			if (firstid(xts_ready[i].queue_head) == lastid(xts_ready[i].queue_head)) {
				xts_ready[i].status = 0;
			}
			return dequeue(xts_ready[i].queue_head);
		}
	}
	return 0;
}
