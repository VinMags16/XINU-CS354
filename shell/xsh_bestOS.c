/* xsh_bestOS.c - xsh_bestOS */

#include <xinu.h>
#include <stdio.h>

/*-------------------------------------------------
 * xsh_bestOS - displays the best OS to window
 *-------------------------------------------------
 */
shellcmd xsh_bestOS(int nargs, char * args[])
{
	/* Check if there's no args */
	
	if (nargs > 1) {
		fprintf(stderr, "Use: bestOS\n");
	}

	printf("XINU\n");
	return 0;
}
