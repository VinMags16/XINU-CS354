#include <xinu.h>

void parent()
{
//	kprintf("In parent\n");
	if (sigcbreg(XSIGRCV, &recvcb, NULL) != OK) {
		kprintf("Callback registration failed!\n");
		return;
	}
	if (sigcbreg(XSIGCHL, &childcb, NULL) != OK) {
		kprintf("Callback registration failed!\n");
		return;
	}
	resume(create((void*)child, 2048, 10, "child", 0, NULL));
	sleepms(1000);
	for (int i = 0; i < 10; i++);
}
