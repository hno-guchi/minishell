/*
 * The Linux Programming Interface
 * 44. Pipes and FIFOs
 *  3. Pipes as a Method of Process Synchronization
 *
 * Listen 44-3: Using a pipe to Synchronize multiple processes
 */

/* Declaration of currTime(); */
#include "curr_time.h"
#include "tlpi_hdr.h"

int	main(int argc, char *argv[])
{
	/* Process synchronization pipe */
	int	pfd[2];
	int	j;
	int	dummy;

	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s sleep-time...\n", argv[0]);
	}
	/* Make stdout unbuffed, since we terminate child with _exit(); */
	setbuf(stdout, NULL);
	printf("%s Parent started\n", currTime("%T"));
	if (pipe(pfd) == -1)
	{
		errExit("pipe");
	}
	for (j = 1; j < argc; j++)
	{
		switch (fork())
		{
			case -1:
				errExit("fork");
			/* Child */
			case 0:
				/* Read end unused */
				if (close(pfd[0]) == -1)
				{
					errExit("close");
				}

				/* Child does some work, and lets parent know it's done. */

				sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
				/* Simulate processing */
				printf("%s	Child %d (PID=%ld) closing pipe\n", currTime("%T"), j, (long)getpid());
				if (close(pfd[1]) == -1)
				{
					errExit("close");
				}

				/* Child now carries on to do other thing... */

				_exit(EXIT_SUCCESS);
			/* Parent loops to create next child */
			default:
				break ;
		}
	}
	/* Parent come here ; close write end of pipe so we can see EOF */
	/* write end unused */
	if (close(pfd[1]) == -1)
	{
		errExit("close");
	}

	/* Parent may do other work, then synchronizes with children */

	if (read(pfd[0], &dummy, 1) != 0)
	{
		fatal("Parent didn't get EOF");
	}
	printf("%s parent ready to go\n", currTime("%T"));

	/* Parent can now carry on to do other things... */
	
	exit(EXIT_SUCCESS);

}


