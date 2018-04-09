#include <xinu.h>

void child()
{
	for (int i = 0; i < 100000; i++) {
		int x = 1;
		x++;
	}
	kprintf("child ending\n");
}
