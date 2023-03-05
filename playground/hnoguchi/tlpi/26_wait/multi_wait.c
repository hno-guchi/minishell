/*
 * 26 monitoring child process
 * 1 creating and waiting for multiple children
 *
 * Create multiple child process.
 * One per(integer) command-line argument.
 * Each child sleeps for the number of seconds specified in the corresponding command-line argument and then exist.
 * In the meantime,
 * after all children have been created,
 * the parent process repeatdly calls wait() to monitor the terminations of its children.
 * This loop continues until wait() returns -1.
 * (This is not the only approach:
 *  we could alternatively exit the loop when the number of terminated children,
 *  [numDead], matches the number of children created.)
 */

#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include "curr_time.h"
#include "tlpi_hdr.h"

int	main(int argc, char **argv)
{
	// number of children so far waited for
	int		numDead;
	// PID of waited for child
	pid_t	childPid;
	int		j;

	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s sleep-time...\n", argv[0]);
	}
	// disable buffering of stdout
	setbuf(stdout, NULL);

	// create one child for each argument
	for (j = 1; j < argc; j++)
	{
		switch(fork())
		{
			case -1:
				errExit("fork");
			case 0:
				// child sleeps for a while then exist
				printf("[%s] child %d started with PID %ld, sleeping %s seconds\n",
						currTime("%T"), j, (long)getpid(), argv[j]);
				sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
				_exit(EXIT_SUCCESS);
			default:
				// Parent just continues around loop
				break;
		}
	}
	numDead = 0;
	for (;;)
	{
		// Parent waits for each child to exit
		childPid = wait(NULL);
		if (childPid == -1)
		{
			if (errno == ECHILD)
			{
				printf("no more children - bye !\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				// Some other (unexpected) error
				errExit("wait");
			}
		}
		numDead += 1;
		printf("[%s] wait returned child PID %ld (numDead=%d)\n", currTime("%T"), (long)childPid, numDead);
	}
}
