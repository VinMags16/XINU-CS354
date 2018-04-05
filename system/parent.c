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
	resume(create((void*)child, 2048, 10, "child", 0, NULL));
	childwait();
	sleepms(2000);
	for (int i = 0; i < 10; i++);
}
