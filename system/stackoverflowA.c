/* stackoverflowA.c - stackoverflowA */

#include <xinu.h>

void stackoverflowA()
{
	while (TRUE) {
		stackoverflowA();
	}	
}
