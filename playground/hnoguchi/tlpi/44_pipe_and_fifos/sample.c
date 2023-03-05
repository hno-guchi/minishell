/*
 * The Linux Programming Interface
 * 44. Pipes and FIFOs
 *  2. Creating and Using Pipes
 *
 *  Listing 44-1: Steps in creating a pipe to transfer data from a parent to a child
 */

#include <unistd.h>

int	main(void)
{
	int filedes[2];

	/* Create the pipe */
	if (pipe(filedes) == -1)
	{
		errExit("pipe");
	}
	/* Create a child process */ 
	switch(fork()) {
		case -1:
			errExit("fork");
		/* Child process */
		case 0:
			/* Closed unused write end */
			if (close(filedes[1]) == -1)
			{
				errExit("close");
			}
			/* Child now reads from pipe */
			break;
		/* Parent process */
		default:
			/* Closed unused read end */
			if (close(filedes[0]) == -1)
			{
				errExit("close");
			}
			/* Parent now write to pipe */
			break;
	}
}
