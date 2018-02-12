/* newProcess.c - newProcess */

#include <xinu.h>

void	newProcess(const char* filename)
{
	pid_t pid = fork();
	execve(filename, )
}
