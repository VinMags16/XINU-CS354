#include<xinu.h>

void sender()
{
	send(4, "Msg 1");
	send(5, "Msg 2");
	send(6, "Msg 3");
}
