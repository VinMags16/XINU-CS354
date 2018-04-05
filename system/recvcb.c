#include <xinu.h>

int recvcb()
{
	kprintf("%s\n", receive());
	return OK;
}
