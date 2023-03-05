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

#include <sys/param.h>
#include <limits.h>

/*
 * Occure [Resource temporaily unavailable] error
 *
 * [OUTPUT]
 * MAXUPRC(CHILD_MAX) is [266]
 * pid[1173] = [-1]
 * fork failed: Resource temporarily unavailable
 *
 * ~$ ulimit -a
 * ~~~~
 * -u: processes                       1392
 * ~~~~
 */
int	main(void)
{
	int		i;
	pid_t	pid[2000];

	printf("MAXUPRC(CHILD_MAX) is [%d]\n", CHILD_MAX);
	for (i = 0; (pid[i] = fork()) > 0; i++);

	if (pid[i] < 0)
	{
		printf("pid[%d] = [%d]\n", i, pid[i]);
		perror("fork failed");
		exit(1);
	}
	exit (0);
}
