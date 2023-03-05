/*
 * 『The Linux Programming Interface』p.90
 *
 * The check on the prior existence of the file and
 * the creation of the file of the file are performed atomically.
 * To see why this is important, consider the code shown in the Listing5-1,
 * which we might resort to in the absence of the O_EXCL flag.
 *
 * Incorrect code to exclusively open a file
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "error_functions.h"

int	main(int argc, char **argv)
{
	int	fd;

	fd = 0;
	/* Open 1: check if file exists */
	fd = open(argv[1], O_WRONLY);
	if (fd != -1)
	{
		/* Open successed */
		printf("[PID %ld] file \"%s\" already exist\n", (long)getpid(), argv[1]);
		close(fd);
	}
	else
	{
		/* Failed for unexpected reason */
		if (errno != ENOENT)
		{
			errExit("open");
		}
		else
		{
			/* WINDOW FOR FAILURE */
			printf("[PID %ld] file \"%s\" doesn't exist yet.\n", (long)getpid(), argv[1]);
			/* Delay between check and create */
			if (2 < argc)
			{
				/* Suspend execution for 5 seconds */
				sleep(5);
				printf("[PID %ld] done sleeping.\n", (long)getpid());

			}
			fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			if (fd == -1)
			{
				errExit("open");
			}
			/* MAY NOT BE TURE */
			printf("[PID %ld] create file \"%s\" exclusively\n", (long)getpid(), argv[1]);
		}
	}
	exit (0);
}
