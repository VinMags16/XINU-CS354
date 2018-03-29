/* sendmsg.c - sendmsg */

#include <xinu.h>
//#define DEBUG 0

void sendmsg(umsg32 msg)
{
	if (send(3, msg) == SYSERR) {
		kprintf("Error sending message!\n");
	}
	#ifdef DEBUG
		kprintf("Message sent\n");
	#endif
}
