/*
 * The Linux Programming Interface
 * 44. Pipes and FIFOs
 *  2. Creating and Using Pipes
 *
 * Listen 44-2: Using a pipe to communicatie between a parent and child process
 */

#include <sys/wait.h>
#include <tlpi_hdr.h>

# define BUF_SIZE 10

int	main(int argc, char *argv[])
{
	/* pipe filedescriptor */
	int		pfd[2];
	char	buf[BUF_SIZE];
	ssize_t	numRead;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		usageErr("%s string\n", argv[0]);
	}
	/* Create the pipe */
	if (pipe(pfd) == -1)
	{
		errExit("pipe");
	}
	switch (fork())
	{
		case -1:
			errExit("fork");
		/* Child - reads from pipe */
		case 0:
			/* Write end unused */
			if (close(pfd[1]) == -1)
			{
				errExit("close - Child");
			}
			for (;;)
			{
				/* Read data from pipe, echo on stdout */
				numRead = read(pfd[0], buf, BUF_SIZE);
				if (numRead == -1)
				{
					errExit("read");
				}
				/* End Of File */
				if (numRead == 0)
				{
					break ;
				}
				if (write(STDOUT_FILENO, buf, numRead) != numRead)
				{
					fatal("child - partial / failed write");
				}
			}
			write(STDOUT_FILENO, "\n", 1);
			if (close(pfd[0]) == -1)
			{
				errExit("close");
			}
			_exit(EXIT_SUCCESS);
		/* Parent - write to pipe */
		default:
			/* Read end unused */
			if (close(pfd[0]) == -1)
			{
				errExit("close - Parent");
			}
			if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
			{
				fatal("Parent - partial / failed write");
			}
			/* Child will see EOF */
			if (close(pfd[1]) == -1)
			{
				errExit("close");
			}
			/* Wait for child to finish */
			wait(NULL);
			exit(EXIT_SUCCESS);
	}
}
