#include <xinu.h>

int childcb()
{
	kprintf("My child died D:\n");
	return OK;
}
