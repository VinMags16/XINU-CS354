/* receivemsg.c - receivemsg */

#include <xinu.h>

void receivemsg()
{
	sleepms(100);
	kprintf("%s\n", receive());
	sleepms(100);
	kprintf("%s\n", receive());
}
