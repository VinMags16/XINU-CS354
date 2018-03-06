/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	void xdone(void);	/* System "shutdown" procedure		*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Vincent Maggioli */
/* Declaration of multilevel feedback queue and process tabs */
struct xts_tab xts_conf[SOLTS];
struct xts_multifb xts_ready[SOLTS];
/* End changes */

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */
		
	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);
	
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\r\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */
	enable();
	/* Create a process to execute function main() */
	resume (
	   create((void *)main, INITSTK, INITPRIO, "Main process", 0,
           NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* End changes */

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
	
	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize all levels of multi-level feedback queue */

	for (int i = 0; i < SOLTS; i++) {
		qid16 queue = newqueue();
		xts_ready[i].queue_head = queue;
		xts_ready[i].queue_tail = queuetail(queue);
		xts_ready[i].status = 0;
	}

	/* Initialize all levels for quantum modifier */

	xts_conf[0].xts_quantum = 200;
	xts_conf[0].xts_tqexp = 0;
	xts_conf[0].xts_slpret = 50;
	
	xts_conf[1].xts_quantum = 200;
	xts_conf[1].xts_tqexp = 0;
	xts_conf[1].xts_slpret = 50;
	
	xts_conf[2].xts_quantum = 200;
	xts_conf[2].xts_tqexp = 0;
	xts_conf[2].xts_slpret = 50;
	
	xts_conf[3].xts_quantum = 200;
	xts_conf[3].xts_tqexp = 0;
	xts_conf[3].xts_slpret = 50;
	
	xts_conf[4].xts_quantum = 200;
	xts_conf[4].xts_tqexp = 0;
	xts_conf[4].xts_slpret = 50;
	
	xts_conf[5].xts_quantum = 200;
	xts_conf[5].xts_tqexp = 0;
	xts_conf[5].xts_slpret = 50;
	
	xts_conf[6].xts_quantum = 200;
	xts_conf[6].xts_tqexp = 0;
	xts_conf[6].xts_slpret = 50;
	
	xts_conf[7].xts_quantum = 200;
	xts_conf[7].xts_tqexp = 0;
	xts_conf[7].xts_slpret = 50;
	
	xts_conf[8].xts_quantum = 200;
	xts_conf[8].xts_tqexp = 0;
	xts_conf[8].xts_slpret = 50;

	xts_conf[9].xts_quantum = 200;
	xts_conf[9].xts_tqexp = 0;
	xts_conf[9].xts_slpret = 50;
	
	xts_conf[10].xts_quantum = 160;
	xts_conf[10].xts_tqexp = 0;
	xts_conf[10].xts_slpret = 51;
	
	xts_conf[11].xts_quantum = 160;
	xts_conf[11].xts_tqexp = 1;
	xts_conf[11].xts_slpret = 51;
	
	xts_conf[12].xts_quantum = 160;
	xts_conf[12].xts_tqexp = 2;
	xts_conf[12].xts_slpret = 51;
	
	xts_conf[13].xts_quantum = 160;
	xts_conf[13].xts_tqexp = 3;
	xts_conf[13].xts_slpret = 51;
	
	xts_conf[14].xts_quantum = 160;
	xts_conf[14].xts_tqexp = 4;
	xts_conf[14].xts_slpret = 51;
	
	xts_conf[15].xts_quantum = 160;
	xts_conf[15].xts_tqexp = 5;
	xts_conf[15].xts_slpret = 51;
	
	xts_conf[16].xts_quantum = 160;
	xts_conf[16].xts_tqexp = 6;
	xts_conf[16].xts_slpret = 51;
	
	xts_conf[17].xts_quantum = 160;
	xts_conf[17].xts_tqexp = 7;
	xts_conf[17].xts_slpret = 51;
	
	xts_conf[18].xts_quantum = 160;
	xts_conf[18].xts_tqexp = 8;
	xts_conf[18].xts_slpret = 51;
	
	xts_conf[19].xts_quantum = 160;
	xts_conf[19].xts_tqexp = 9;
	xts_conf[19].xts_slpret = 51;
	
	xts_conf[20].xts_quantum = 120;
	xts_conf[20].xts_tqexp = 10;
	xts_conf[20].xts_slpret = 52;
	
	xts_conf[21].xts_quantum = 120;
	xts_conf[21].xts_tqexp = 11;
	xts_conf[21].xts_slpret = 52;
	
	xts_conf[22].xts_quantum = 120;
	xts_conf[22].xts_tqexp = 12;
	xts_conf[22].xts_slpret = 52;
	
	xts_conf[23].xts_quantum = 120;
	xts_conf[23].xts_tqexp = 13;
	xts_conf[23].xts_slpret = 52;
	
	xts_conf[24].xts_quantum = 120;
	xts_conf[24].xts_tqexp = 14;
	xts_conf[24].xts_slpret = 52;
	
	xts_conf[25].xts_quantum = 120;
	xts_conf[25].xts_tqexp = 15;
	xts_conf[25].xts_slpret = 52;
	
	xts_conf[26].xts_quantum = 120;
	xts_conf[26].xts_tqexp = 16;
	xts_conf[26].xts_slpret = 52;
	
	xts_conf[27].xts_quantum = 120;
	xts_conf[27].xts_tqexp = 17;
	xts_conf[27].xts_slpret = 52;
	
	xts_conf[28].xts_quantum = 120;
	xts_conf[28].xts_tqexp = 18;
	xts_conf[28].xts_slpret = 52;
	
	xts_conf[29].xts_quantum = 120;
	xts_conf[29].xts_tqexp = 19;
	xts_conf[29].xts_slpret = 52;
	
	xts_conf[30].xts_quantum = 80;
	xts_conf[30].xts_tqexp = 20;
	xts_conf[30].xts_slpret = 53;
	
	xts_conf[31].xts_quantum = 80;
	xts_conf[31].xts_tqexp = 21;
	xts_conf[31].xts_slpret = 53;
	
	xts_conf[32].xts_quantum = 80;
	xts_conf[32].xts_tqexp = 22;
	xts_conf[32].xts_slpret = 53;
	
	xts_conf[33].xts_quantum = 80;
	xts_conf[33].xts_tqexp = 23;
	xts_conf[33].xts_slpret = 53;
	
	xts_conf[34].xts_quantum = 80;
	xts_conf[34].xts_tqexp = 24;
	xts_conf[34].xts_slpret = 53;
	
	xts_conf[35].xts_quantum = 80;
	xts_conf[35].xts_tqexp = 25;
	xts_conf[35].xts_slpret = 54;
	
	xts_conf[36].xts_quantum = 80;
	xts_conf[36].xts_tqexp = 26;
	xts_conf[36].xts_slpret = 54;
	
	xts_conf[37].xts_quantum = 80;
	xts_conf[37].xts_tqexp = 27;
	xts_conf[37].xts_slpret = 54;
	
	xts_conf[38].xts_quantum = 80;
	xts_conf[38].xts_tqexp = 28;
	xts_conf[38].xts_slpret = 54;
	
	xts_conf[39].xts_quantum = 80;
	xts_conf[39].xts_tqexp = 29;
	xts_conf[39].xts_slpret = 54;
	
	xts_conf[40].xts_quantum = 40;
	xts_conf[40].xts_tqexp = 30;
	xts_conf[40].xts_slpret = 55;
	
	xts_conf[41].xts_quantum = 40;
	xts_conf[41].xts_tqexp = 31;
	xts_conf[41].xts_slpret = 55;
	
	xts_conf[42].xts_quantum = 40;
	xts_conf[42].xts_tqexp = 32;
	xts_conf[42].xts_slpret = 55;
	
	xts_conf[43].xts_quantum = 40;
	xts_conf[43].xts_tqexp = 33;
	xts_conf[43].xts_slpret = 55;
	
	xts_conf[44].xts_quantum = 40;
	xts_conf[44].xts_tqexp = 34;
	xts_conf[44].xts_slpret = 55;
	
	xts_conf[45].xts_quantum = 40;
	xts_conf[45].xts_tqexp = 35;
	xts_conf[45].xts_slpret = 56;
	
	xts_conf[46].xts_quantum = 40;
	xts_conf[46].xts_tqexp = 36;
	xts_conf[46].xts_slpret = 57;
	
	xts_conf[47].xts_quantum = 40;
	xts_conf[47].xts_tqexp = 37;
	xts_conf[47].xts_slpret = 58;
	
	xts_conf[48].xts_quantum = 40;
	xts_conf[48].xts_tqexp = 38;
	xts_conf[48].xts_slpret = 58;
	
	xts_conf[49].xts_quantum = 40;
	xts_conf[49].xts_tqexp = 39;
	xts_conf[49].xts_slpret = 58;
	
	xts_conf[50].xts_quantum = 40;
	xts_conf[50].xts_tqexp = 40;
	xts_conf[50].xts_slpret = 58;
	
	xts_conf[51].xts_quantum = 40;
	xts_conf[51].xts_tqexp = 41;
	xts_conf[51].xts_slpret = 58;
	
	xts_conf[52].xts_quantum = 40;
	xts_conf[52].xts_tqexp = 42;
	xts_conf[52].xts_slpret = 58;
	
	xts_conf[53].xts_quantum = 40;
	xts_conf[53].xts_tqexp = 43;
	xts_conf[53].xts_slpret = 58;
	
	xts_conf[54].xts_quantum = 40;
	xts_conf[54].xts_tqexp = 44;
	xts_conf[54].xts_slpret = 58;
	
	xts_conf[55].xts_quantum = 40;
	xts_conf[55].xts_tqexp = 45;
	xts_conf[55].xts_slpret = 58;
	
	xts_conf[56].xts_quantum = 40;
	xts_conf[56].xts_tqexp = 46;
	xts_conf[56].xts_slpret = 58;
	
	xts_conf[57].xts_quantum = 40;
	xts_conf[57].xts_tqexp = 47;
	xts_conf[57].xts_slpret = 58;
	
	xts_conf[58].xts_quantum = 40;
	xts_conf[58].xts_tqexp = 48;
	xts_conf[58].xts_slpret = 58;
	
	xts_conf[59].xts_quantum = 20;
	xts_conf[59].xts_tqexp = 49;
	xts_conf[59].xts_slpret = 59;

	/* End changes*/

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}

	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
