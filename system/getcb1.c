/* getcb.c - getcb */

#include <xinu.h>

syscall getcb1()
{
	intmask mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	int (*fnptr)() = prptr->fptr1;
	restore(mask);
	return fnptr;
}
