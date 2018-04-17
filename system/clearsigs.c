#include <xinu.h>

syscall clearsigs()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	for (int i = 0; i < 3; i++) {
		prptr->sigqueue[i] = 0;
	}
	restore(mask);
	return OK;
}
