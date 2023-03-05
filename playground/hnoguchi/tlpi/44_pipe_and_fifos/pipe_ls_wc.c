/*
 * The Linux Programming Interface
 * 44. Pipes and FIFOs
 *  4. Using Pipes to Connect Filtes
 *
 * Listen 44-4: Using a pipe to connect [ls] and [wc]
 */

#include <sys/wait.h>
#include "tlpi_hdr.h"

int	main(int argc, char *argv[])
{
	/* Pipe file descriptor */
	int	pfd[2];

	/* Create pipe */
	if (pipe(pfd) == -1)
	{
		errExit("pipe");
	}
	switch (fork())
	{
		case -1:
			errExit("fork");
		/* First child: exec `ls' to write to pipe */
		case 0:
			/* Read end unused */
			if (close(pfd[0]) == -1)
			{
				errExit("close 1");
			}
			/* Duplicate stdout on write end of pipe; close duplicated descriptor */
			/* Defensive check */
			if (pfd[1] != STDOUT_FILENO)
			{
				if (close(STDOUT_FILENO) == -1)
				{
					errExit("close 2");
				}
				if (dup2(pfd[1], STDOUT_FILENO) == -1)
				{
					errExit("dup2 1");
				}
				if (close(pfd[1]) == -1)
				{
					errExit("close 3");
				}
			}
			/* write to pipe */
			execlp("ls", "ls", (char *)NULL);
			errExit("execlp ls");
		/* Parent falls through to create next child */
		default:
			break ;
	}
	switch (fork())
	{
		case -1:
			errExit("fork");
		/* Second child: exec 'wc' to read from pipe  */
		case 0:
			/* write end unused */
			if (close(pfd[1]) == -1)
			{
				errExit("close 4");
			}
			/* Duplicate stdin on read end pipe; close duplicated descriptor */
			/* Defensive check */
			if (pfd[0] != STDIN_FILENO)
			{
				if (close(STDIN_FILENO) == -1)
				{
					errExit("close 5");
				}
				if (dup2(pfd[0], STDIN_FILENO) == -1)
				{
					errExit("dup2 2");
				}
				if (close(pfd[0]) == -1)
				{
					errExit("close 6");
				}
			}
			/* Read from pipe */
			execlp("wc", "wc", "-l", (char *)NULL);
			errExit("execlp wc -l");
		/* Parent falls through */
		default:
			break ;
	}
	/* Parent closes unused file descriptors for pipe, and waits for children */
	if (close(pfd[0]) == -1)
	{
		errExit("close 7");
	}
	if (close(pfd[1]) == -1)
	{
		errExit("close 8");
	}
	if (wait(NULL) == -1)
	{
		errExit("wait 1");
	}
	if (wait(NULL) == -1)
	{
		errExit("wait 2");
	}
	exit(EXIT_SUCCESS);
}
