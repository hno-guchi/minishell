#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "sample.h"

static void	charatatime(char *str)
{
	char	*ptr;
	int		c;

	/* アンバッファドにする */
	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0; )
	{
		putc(c, stdout);
	}
}

/*
 * race conditionあり
int	main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		charatatime("output from child\n");
	}
	else
	{
		charatatime("output from parent\n");
	}
	return (0);
}
*/

/*
 * race conditionなし
 */
int	main(void)
{
	pid_t	pid;

	TELL_WAIT();
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		/* parentが先行 */
		WAIT_PARENT();
		charatatime("output from child\n");
	}
	else
	{
		charatatime("output from parent\n");
		TELL_CHILD(pid);
	}
	return (0);
}

/*
 * childが先行
 * else if (pid == 0)
 * {
 * 		charatatime("output from child\n");
 * 		TELL_PARENT(getppid());
 * }
 * else
 * {
 * 		WAIT_CHILD();
 * 		charatatime("output from parent\n");
 * }
 * */
