/* iotest.c - iotest */

#include <xinu.h>

void iotest() {
	resume(create((void*)iobound, 2048, 1, "io1", 0, NULL));
	resume(create((void*)iobound, 2048, 5, "io2", 0, NULL));
	resume(create((void*)iobound, 2048, 10, "io3", 0, NULL));
	resume(create((void*)iobound, 2048, 15, "io4", 0, NULL));
	resume(create((void*)iobound, 2048, 20, "io5", 0, NULL));
}
