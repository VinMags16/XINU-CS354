/* xts_priochk.c - xts_priochk */

#include <xinu.h>

pri16 xts_priochk()
{
	for (int i = SOLTS - 1; i >=0; i++) {
		if (xts_ready[i].status) {
			return (pri16) i;
		}
	}
	return 0;
}
