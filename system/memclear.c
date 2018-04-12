#include <xinu.h>

void memclear()
{
	struct procent *prptr;

	prptr = &proctab[currpid];
	for (int i = 0; i < 100; i++) {
		if (strcmp(prptr->prmemlist[i], NULL) != 0) {
			freemem(prptr->prmemlist[i], 16);
		}
	}
}
