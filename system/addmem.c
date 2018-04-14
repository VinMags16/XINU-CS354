#include <xinu.h>


void addmem(struct memblk *mem)
{
	struct procent *prptr;
	struct memblk *curr;

	prptr = &proctab[currpid];
	curr = prptr->prmemlist.mnext;
	if (curr == NULL) {
		prptr->prmemlist.mnext = mem;
		mem->mnext = NULL;
		prptr->prmemlist.mlength += mem->mlength;
		return;
	}
	while (curr->mnext != NULL && curr->mnext != (void*)0xffffffff) {
		kprintf("0x%x\n", curr->mnext);
		curr = curr->mnext;
	}
	curr->mnext = mem;
	mem->mnext = NULL;
	prptr->prmemlist.mlength += mem->mlength;
}
