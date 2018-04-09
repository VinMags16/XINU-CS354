#include <xinu.h>

int childcb()
{
	int x = 1;
	x++;
	return OK;
}
