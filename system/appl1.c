/* appl1.c - appl1, fun1 */

#include <xinu.h>

char fun1(char a, char b)
{
	kprintf("\n\n3. after appl1() calls fun1() and before fun1() returns:\n");
	kprintf("Base of the stack : Address - 0x%04x, Value - 0x%04x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg asm("esp");
	char* bytes = (char*)reg;
	kprintf("Top of the stack : Address - 0x%04x, Value - 0x04%x", bytes, &bytes);
	return a+b;
}

int appl1()
{
	kprintf("\n\n2. after appl1() is created before fun1() is called:\n");
	kprintf("Base of the stack: Address - 0x%04x, Value - 0x%04x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg asm("esp");	
	char* bytes = (char*)reg;
	kprintf("Top of the stack : Address - 0x%04x, Value - 0x04%x", bytes, &bytes);
	
	int res = (int)fun1('<','%');

	kprintf("\n\n4. after appl1() calls fun1() and after fun1() has returned:\n");
	kprintf("Base of the stack: Address - 0x%04x, Value - 0x%04x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg2 asm("esp");	
	char* bytes2 = (char*)reg2;
	kprintf("Top of the stack : Address - 0x%04x, Value - 0x04%x", bytes2, &bytes2);

	return res;
}

