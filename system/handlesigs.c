#include <xinu.h>

syscall	handlesigs()
{
	intmask	mask;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];
	for (int i = 0; i < 3; i++) {
		struct sigent *ent = &prptr->sigqueue[i];
		if (ent->ssig != NULL) {
			switch(ent->ssig) {
				case XSIGRCV:
					if (prptr->prhascb) {
						int(*fnptr)() = prptr->fptr;
						(*fnptr)();
					}
					break;
				case XSIGCHL:
					if (prptr->prhascb1) {
						int(*fnptr)() = prptr->fptr1;
						(*fnptr)();
					}
					break;
				case XSIGXTM:
					if (prptr->prhascb2) {
						int(*fnptr)() = prptr->fptr2;
						(*fnptr)();	
					}
					break;
			}
		} else {
			break;
		}
	}
	restore(mask);
	return OK;
}
