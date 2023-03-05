/*
 * #include <sys/wait.h>
 * pid_t	wait(int *stat_loc);
 *
 * wait for process termination
 *
 * RETURN VALUES
 * [success]
 * stopped or terminated child process,
 * the process ID of the child is returned to the calling process.
 * [failed]
 * -1 and set errno
 *
 *  ERROR
 *  [ECHILD]
 *  The calling process has no existing unwaited-for child processes.
 */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	main(void)
{
	pid_t	child_pid;
	pid_t	wait_pid;

	child_pid = fork();
	wait_pid = 0;
	if (child_pid < 0)
	{
		perror("fork");
	}
	else if (child_pid == 0)
	{
		sleep(2);
		exit(0);
	}
	else
	{
		while (wait_pid != -1)
		{
			sleep(1);
			wait_pid = wait(NULL);
		}
		if (errno != ECHILD)
		{
			perror("wait");
		}
		else
		{
			perror("wait (ECHILD)");
		}
	}
	exit (0);
}
