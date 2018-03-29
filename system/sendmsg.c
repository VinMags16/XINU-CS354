/* sendmsg.c - sendmsg */

#include <xinu.h>
#define DEBUG 0

void sendmsg(umsg32 msg)
{
	kprintf("Sending to 3\n");
	send(3, msg);
	#ifdef DEBUG
		kprintf("Message sent\n");
	#endif
}
