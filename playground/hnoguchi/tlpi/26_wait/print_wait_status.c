/*
 * 26 monitoring child process
 * 1.3 The wait status value
 *
 * p.546 Displaying the status value returned by wait(); and related calls
 */
# define _GNU_SOURCE
#include <string.h>
#include <sys/wait.h>
// #include "print_wait_status.h"
#include "tlpi_hdr.h"

void	printWaitStatus(const char *msg, int status)
{
	if (msg != NULL)
	{
		printf("%s", msg);
	}
	if (WIFEXITED(status))
	{
		printf("child exited, status=%d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("child killed by signal %d (%s)", WTERMSIG(status), strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP // Not in SUSv3, maybe absent on some systems
		if (WCOREDUMP(status))
		{
			printf(" (core dump)");
		}
#endif
		printf("\n");
	}
	else if (WIFSTOPPED(status))
	{
		printf("child stopped by signal %d (%s)\n", WSTOPSIG(status), strsignal(WSTOPSIG(status)));
	}
#ifdef WIFCONTINUED // SUSv3 has this, but older linux version and some other UNIX implementations do'nt.
	else if (WIFCONTINUED(status))
	{
		printf("child continued\n");
	}
#endif
	else
	{
		// should never happen
		printf("what happned to this child? (status=%x)\n", (unsigned int)status);
	}
}
