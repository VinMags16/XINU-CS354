/* cdhandler.c - cdhandler */

#include <xinu.h>
//#define DEBUG 0
void cbhandler()
{
	uint32 *sigqueue = getsigqueue();
	if (sigqueue[0] == 0) {
		return;
	}
	for (int i = 0; i < 3; i++) {
		int (*fnptr)();
		switch(sigqueue[i]) {
			case XSIGRCV:
				fnptr = getcbrcv();
				if (fnptr != SYSERR) {
					(*fnptr)();
				}
				clearsigrcv();
				break;
			case XSIGCHL:
				fnptr = getcbchl();
				if (fnptr != SYSERR) {
					(*fnptr)();
				}
				clearsigchl();
				break;
			case XSIGXTM:
				fnptr = getcbxtm();
				if (fnptr != SYSERR) {
					(*fnptr)();
				}
				clearsigxtm();
				break;
			default:
				break;
		};
		sigqueue[i] = 0;
	}
}
