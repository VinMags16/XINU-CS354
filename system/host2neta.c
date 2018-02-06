/* host2neta.c - host2neta */

#include <xinu.h>

long host2neta(long x)
{
	long res;
	asm("movl %1, %0\n\t"
		"rol $8, %%eax\n\t"
		"xchg %%al, %%ah\n\t"
		"ror $8, %%eax\n\t"
		"movl %%eax, %0"
		: "=r" (res)
		: "r" (x)
		: "%eax");
	return res;
}
