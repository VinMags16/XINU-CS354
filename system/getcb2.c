/* getcb.c - getcb */

#include <xinu.h>

syscall getcb2()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	int (*fnptr)() = prptr->fptr2;
	restore(mask);
	return fnptr;
}
