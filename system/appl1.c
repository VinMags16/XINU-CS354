/* appl1.c - appl1, fun1 */

#include <xinu.h>

char fun1(char a, char b)
{
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	return a+b;
}

int appl1()
{
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	int res = (int)fun1('<','%');
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	return res;
}

