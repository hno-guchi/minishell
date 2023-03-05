/*
 * #include <unistd.h>
 * pid_t	fork(void);
 *
 * create a new process
 */

/* child processで変数の変更を行なっても、Parent processの値に影響しない */

#include <unistd.h>
#include <stdio.h>

int		globvar = 6;
char	buf[] = "a write to stdout\n";

int	main(void)
{
	/* stack上の自動変数 */
	int		var;
	pid_t	pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, (sizeof(buf) - 1)) != (sizeof(buf) - 1))
	{
		fprintf(stderr, "write error\n");
		return (0);
	}
	/* 標準出力をフラッシュしない */
	printf("before fork\n");
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
		return (0);
	}
	else if (pid == 0)
	{
		/* child process */
		globvar += 1;
		var += 1;
	}
	else
	{
		/* Parent process */
		sleep(2);
	}
	printf("pid = [%ld], glob = [%d], var = [%d]\n", (long)getpid(), globvar, var);
	return (0);
}
