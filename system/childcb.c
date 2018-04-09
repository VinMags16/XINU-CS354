#include <xinu.h>

int childcb()
{
	kprintf("My child died D: %d\n", currpid);
	return OK;
}
