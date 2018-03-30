/* cdhandler.c - cdhandler */

#include <xinu.h>
//#define DEBUG 0
void cbhandler()
{
	#ifdef DEBUG
		if (currpid == 4) {
			kprintf("cb handler 4 %d:%d\n", proctab[currpid].prhasmsg, proctab[currpid].prhascb);
		}
	#endif
	if (hascb() == OK) {
		int (*fnptr)() = getcb();
		(*fnptr)();
	}
}
