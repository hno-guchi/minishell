/*
 * #include <unistd.h>
 * int	pipe(int fildes[2]);
 *
 * create descriptor pair for interprocess communication
 *
 * パイプを介して親から子へデータを送る
 */

#include "pipe.h"

int	main(void)
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe(fd) < 0)
	{
		err_sys("pipe error");
	}

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (0 < pid)
	{
		/* Parent */
		close(fd[0]);
		write(fd[1], "Hello, world\n", 12);
	}
	else
	{
		/* Child */
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
