#include <xinu.h>

int childcb()
{
//	kprintf("%d died\n", childwait());
	int x = 1;
	x++;
	return OK;
}
