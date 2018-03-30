/* test.c - test */

#include <xinu.h>
#define DEBUG 0

void test()
{
	resume(create((void*)testproc, 2048, 15, "testproc1", 0, NULL));
	send(4, "Message for pid 4");
	resume(create((void*)testproc, 2048, 10, "testproc2", 0, NULL));
	send(5, "Message for pid 5");
	resume(create((void*)testproc, 2048, 5, "testproc3", 0, NULL));
	send(6, "Message for pid 6");
}
