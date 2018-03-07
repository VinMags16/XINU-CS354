/* cputest.c - cputest */

#include <xinu.h>

void cputest() {
	resume(create((void*)cpubound, 2048, 1, "cpu1", 0, NULL));
	resume(create((void*)cpubound, 2048, 5, "cpu2", 0, NULL));
	resume(create((void*)cpubound, 2048, 10, "cpu3", 0, NULL));
	resume(create((void*)cpubound, 2048, 15, "cpu4", 0, NULL));
	resume(create((void*)cpubound, 2048, 20, "cpu5", 0, NULL));
}
