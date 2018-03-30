/* mrecv_cb.c - mrecv_cb */

#include <xinu.h>

int32 mrecv_cb()
{
	kprintf("%d:%d\n", receive(), getpid());
	return OK;
}
