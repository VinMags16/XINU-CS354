#include <xinu.h>

int removemem(struct memblk *mem, uint32 length)
{
	struct procent *prptr;
	struct memblk	*prev;
	struct memblk	*curr;
	struct memblk *next;

	prptr = &proctab[currpid];
	prev = &prptr->prmemlist;
	curr = prptr->prmemlist.mnext;
	next = curr->mnext;
	while (curr != NULL) {
		if (curr == mem) {
			if (curr->mlength <= length) {
				prev->mnext = next;
				prptr->prmemlist.mlength -= length;
				return OK;
			} else {
				curr->mlength -= length;
				prptr->prmemlist.mlength -= length;
				return OK;
			}
		}
		prev = curr;
		curr = curr->mnext;
		next = curr->mnext;
	}
	return SYSERR;
}
