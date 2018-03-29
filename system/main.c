/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

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
	recvclr();
	
	/* Part 3 */
//	resume(create((void*)receivemsg, 2048, 5, "receivemsg", 0, NULL));
//	resume(create((void*)sendmsg, 2048, 2, "sendmsg1", 1, "Message 1"));
//	resume(create((void*)sendmsg, 2048, 2, "sendmsg2", 1, "Message 2"));

	/* Part 4 */
	resume(create((void*)test, 2048, 5, "test", 0, NULL));
	resume(create((void*)sendmsg, 2048, 2, "sendmsg", 1, "Hello world"));

//	kill(2);
}
