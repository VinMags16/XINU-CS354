/* host2netca.c - host2netca */

#include <xinu.h>

long host2netca(long x)
{
	long x1, x2, x3, x4;
	x1 = (x & 0x000000ff) << 24u;
	x2 = (x & 0x0000ff00) << 8u;
	x3 = (x & 0x00ff0000) >> 8u;
	x4 = (x & 0xff000000) >> 24u;
	long res = x1 | x2 | x3 | x4;
	return res;
}
