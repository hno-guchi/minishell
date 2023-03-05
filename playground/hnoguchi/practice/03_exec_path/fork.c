/*
 * #include <sys/types.h>
 * #include <unistd.h>
 * pid_t	fork(void);
 *
 * create a new process
 *
 * RETURN VALUE
 * Success
 * 0 to the child process.
 * The child process ID to the parent process.
 * Other
 * -1 to the parent process, and do'nt create child process,
 * and set the glocal variable [errno].
 *
 * CAVEATS
 * There are limits to what you can do in the child process.
 * Until such time as one of the exec function is called,
 * must use async-signal safe operation.
 * If you need to use these async-signal unsafe operation in the child process, you must such time as one of the exec function.
 * In this situation it is reasonable to exec yourself.
*/

#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	main(void)
{
	int		num;
	pid_t	pid;

	num = 10;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
	}
	else if (pid == 0)
	{
		/* child process */
		num += 32;
	}
	else
	{
		/* Parent process */
		sleep(2);
	}
	printf("pid[%d] : num = [%d]\n", getpid(), num);
	exit (0);
}
