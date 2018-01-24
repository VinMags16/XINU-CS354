/* xsh_lab1cmd.c - xsh_lab1cmd */

#include <xinu.h>
#include <stdio.h>

/*-------------------------------------------------
 * xsh_lab1cmd - displays the best OS to window
 *-------------------------------------------------
 */
shellcmd xsh_lab1cmd(int nargs, char * args[])
{
	/* Check if there's no args */
	
	if (nargs > 1) {
		fprintf(stderr, "Use: bestOS\n");
	}

	printf("XINU\n");
	return 0;
}
