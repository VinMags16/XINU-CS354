/* mixedtest.c - mixedtest */

#include <xinu.h>

void mixedtest() {
	resume(create((void*)cpubound, 2048, 1, "cpu1", 0, NULL));
	resume(create((void*)iobound, 2048, 1, "io1", 0, NULL));
	resume(create((void*)cpubound, 2048, 10, "cpu2", 0, NULL));
	resume(create((void*)iobound, 2048, 10, "io2", 0, NULL));
	resume(create((void*)cpubound, 2048, 20, "cpu3", 0, NULL));
	resume(create((void*)iobound, 2048, 20, "io3", 0, NULL));
}
