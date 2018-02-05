/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	kprintf("\n...creating a shell\n");
	kprintf("\n(Maggioli, Vincent)\n");
	kprintf("\nvmaggiol\n");
	
	/* Part 3 code  */
	//host2net(1);
	
	/* Part 4.1 code */	

	//resume(create((void*)stackoverflowA, 2048, 10, "overflowA", 0, NULL));
	//resume(create((void*)stackoverflowB, 2000, 15, "overflowB", 0, NULL));
	//sleepms(3000);
	
	/* Part 4.2 code */
	kprintf("\nBase of runtime stack = 0x%x : 0x%x\n", proctab[currpid].prstkbase, &(proctab[currpid].prstkbase));
	// TODO use in-line assembly to print same info about top of stack

	resume(create((void*)appl1, 2048, INITPRIO, "appl1", 0, NULL));	


	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
