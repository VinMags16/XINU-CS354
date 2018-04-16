#include <xinu.h>

int childcb()
{
	int x = 1;
	x++;
	kprintf("Dead child: %d\n", childwait());
	return OK;
}
