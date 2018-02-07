/* stackoverflowB.c - stackoverflowB */

#include <xinu.h>

void stackoverflowB()
{
	char b = 'B';
	kprintf("%c\n", b);	
	sleepms(1500);
	kprintf("%c\n", b);
}
