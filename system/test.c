/* test.c - test */
#include <test.h>
#include <xinu.h>

void test()
{
	for (int i = 0; i < UPBOUND; i++) { }
	printf("\n%d\n", getcputot(currpid));
}
