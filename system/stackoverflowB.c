/* stackoverflowB.c - stackoverflowB */

#include <xinu.h>

void stackoverflowB()
{
	char b = 'B';
	while (TRUE) {
		putc(b, stdout);
		sleepms(1500);
	}
}
