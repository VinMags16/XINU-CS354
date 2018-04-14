#include <xinu.h>

void memclear()
{
	struct procent *prptr;
	struct memblk *curr;
	struct memblk *node;

	prptr = &proctab[currpid];
	curr = prptr->prmemlist.mnext;
	if (curr == NULL) {
		return;
	}
	while (curr != NULL) {
		node = curr;
		curr = curr->mnext;
		freemem((char*)node, node->mlength);
	}
}
