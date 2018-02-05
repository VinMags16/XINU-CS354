/* appl1.c - appl1, fun1 */

#include <xinu.h>

char fun1(char a, char b)
{
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg asm("esp");
	kprintf("Top of runtime stack = 0x%x : ", reg);
	char* bytes = reg;
	printf("0x%04x\n\n", &bytes);

	return a+b;
}

int appl1()
{
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg asm("esp");
	kprintf("Top of runtime stack = 0x%x : ", reg);
	char* bytes = reg;
	printf("0x%04x\n\n", &bytes);
		
	int res = (int)fun1('<','%');
	
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	register long reg2 asm("esp");
	kprintf("Top of runtime stack = 0x%x : ", reg);
	char* bytes2 = reg2;
	printf("0x%04x\n\n", bytes2);
		
	return res;
}

