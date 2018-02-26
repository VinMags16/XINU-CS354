/* xts_dequeue.c - xts_dequeue */

#include <xinu.h>

pid32 xts_dequeue()
{
	for (int i = 59; i > -1; i--) {
		if (xts_ready[i].status) {
			
			return ;
		}
	} 	
	return 0;
}
