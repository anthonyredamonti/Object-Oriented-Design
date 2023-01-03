/* xsh_signaln.c - xsh_signaln */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_signaln - shell command to create a process
 *------------------------------------------------------------------------
 */
shellcmd xsh_signaln(int nargs, char *args[])
{
	pid32	pid;			/* return PID			*/
	int32	n;	    /* number of processes to signal		*/
	char	ch;				/* next character of argument	*/
	char	*chptr;			/* walks along argument string	*/

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s Priority\n\n", args[0]);
		printf("Description:\n");
		printf("\tcreates a process\n");
		printf("Options:\n");
		printf("\tPriority \tthe priority of a process to create\n");
		printf("\t\t If no priority provided, a default value\n");
		printf("\t\t of 20 is used\n");
		printf("\t--help\tdisplay this help and exit\n");
		return OK;
	}

	/* Check argument count */

	if (nargs != 2) {
		fprintf(stderr, "%s: incorrect argument\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return SYSERR;
	}

	/* compute priority from argument string */
	
	if (nargs == 2) {
		chptr = args[1];
		ch = *chptr++;
		n = 0;
		while(ch != NULLCH) {
			if ( (ch < '0') || (ch > '9') ) {
				fprintf(stderr, "%s: non-digit in process ID\n",
					args[0]);
				return 1;
			}
			n = 10*n + (ch - '0');
			ch = *chptr++;
		}
		signaln(globalsemaphore, n);
		//pid = create(runforever, 1024, priority, "p 1", 0);
		if (pid == SYSERR) {
			fprintf(stderr, "%s: cannot create process %d\n",
				args[0], n);
			return 1;
		}
		resume(pid);
	}
	return 0;
}
