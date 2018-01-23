/* onAndOn.c - onAndOn  */

#include <xinu.h>
#include <signal.h>

void onAndOn()
{
	while (true) {
		putc(CONSOLE, 'x');
		sleep(2);
	}	
}
