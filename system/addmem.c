#include <xinu.h>

void addmem(char* mem)
{
	struct procent *prptr;

	prptr = &proctab[currpid];
	for (int i = 0; i < 100; i++) {
		if (strcmp(prptr->prmemlist[i], NULL) == 0) {
			prptr->prmemlist[i] = mem;
			break;
		}
	}
}
