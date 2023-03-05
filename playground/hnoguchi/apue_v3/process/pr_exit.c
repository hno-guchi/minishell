/*
 * #include <sys/wait.h>
 * pid_t	wait(int *stat_loc);
 *
 * wait for process termination.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	pr_exit(int status)
{
	if (WIFEXITED(status))
	{
		printf("normal termination, exit status = [%d]\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("abnormal termination, signal number = [%d]%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
#else
			"");
#endif
	}
	else if (WIFSTOPPED(status))
	{
		printf("child stopped. signal number = [%d]\n", WSTOPSIG(status));
	}
}

int	main(void)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
	}
	else if (pid == 0)
	{
		/* child process */
		exit(7);
	}

	/* childを待つ */
	if (wait(&status) != pid)
	{
		fprintf(stderr, "wait error");
	}
	/* statusを表示 */
	pr_exit(status);

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
	}
	else if (pid == 0)
	{
		/* child process */
		/* SIGABRTを生成 */
		abort();
	}

	/* childを待つ */
	if (wait(&status) != pid)
	{
		fprintf(stderr, "wait error");
	}
	/* statusを表示 */
	pr_exit(status);

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
	}
	else if (pid == 0)
	{
		/* child process */
		/* ゼロ除算でSIGFPEを生成 */
		status /= 0;
	}

	if (wait(&status) != pid)
	{
		/* 子を待つ */
		fprintf(stderr, "wait error");
	}
	pr_exit(status);

	return (0);
}
