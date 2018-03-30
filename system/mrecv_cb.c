/* mrecv_cb.c - mrecv_cb */

#include <xinu.h>

int32 mrecv_cb()
{
	kprintf("%s\n", receive());
	return OK;
}
