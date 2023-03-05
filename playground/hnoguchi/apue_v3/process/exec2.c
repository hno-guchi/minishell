/*
 * 解釈実行ファイルをexecするプログラム
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "sample.h"

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		/* child process */
		if (execl("testinterp", "testinterp", "myarg1", "MY ARG2", (char *)0) < 0)
		{
			err_sys("execl error");
		}
	}

	/* Parent process */
	if (waitpid(pid, NULL, 0) < 0)
	{
		err_sys("waitpid error");
	}
	return (0);
}
