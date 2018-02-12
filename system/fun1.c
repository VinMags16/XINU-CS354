/* fun1.c - fun1 */

#include <xinu.h>

char fun1(char a, char b)
{
	kprintf("3. after appl1() calls fun1() and before fun1() returns:\n");
	kprintf("Base of the stack : Address - 0x%04x, Value - 0x%04x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register char* reg asm("esp");
	char* bytes = reg;
	kprintf("Top of the stack : Address - 0x%04x, Value -0x%04x\n\n", bytes, &bytes);
	return a+b;
}
