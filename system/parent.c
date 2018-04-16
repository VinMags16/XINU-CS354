#include <xinu.h>

void parent()
{
	if (sigcbreg(XSIGRCV, &recvcb, NULL) != OK) {
		kprintf("Callback registration failed!\n");
		return;
	}
	if (sigcbreg(XSIGCHL, &childcb, NULL) != OK) {
		kprintf("Callback registration failed!\n");
		return;
	}
	if (sigcbreg(XSIGXTM, &xtmcb, 1) != OK) {
		kprintf("Callback regsitration failed!\n");
		return;
	}

	/* Test recv */
	// Main sends message in order to avoid having child process 
//	sleepms(1000);

	/* Test chld */
//	kprintf("Before creation\n");
	resume(create((void*)child, 2048, 6, "child", 0, NULL));
	resume(create((void*)child, 2048, 7, "child", 0, NULL));
//	kprintf("My child, %d, died D:\n", childwait());
//	kprintf("My child, %d, died D:\n", childwait());
	/* Test xtm */
//	sleepms(2000);
}
