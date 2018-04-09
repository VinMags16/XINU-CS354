#include <xinu.h>

void child()
{
	for (int i = 0; i < 100000000; i++) {
		int x = 1;
		x++;
	}
}
