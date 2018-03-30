/* cdhandler.c - cdhandler */

#include <xinu.h>

void cbhandler()
{
	if (currpid > 3) {
		kprintf("cbhandler %d\n", currpid);
	}
	getcb();
}
