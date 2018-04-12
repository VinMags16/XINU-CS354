#include <xinu.h>

int removemem(char* mem)
{
	struct procent *prptr;

	prptr = &proctab[currpid];
	for (int i = 0; i < 100; i++) {
		if (prptr->prmemlist[i] == mem) {
			prptr->prmemlist[i] = NULL;
			return OK;
		}
	}
	return SYSERR;
}
