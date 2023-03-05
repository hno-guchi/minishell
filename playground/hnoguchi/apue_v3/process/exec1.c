#include <unistd.h>
#include <sys/wait.h>
#include "sample.h"

char	*env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int	main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		/* パス名・環境を指定 */
		if (execle("echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
		{
			err_sys("execle error");
		}
	}

	if (waitpid(pid, NULL, 0) < 0)
	{
		err_sys("wait error");
	}

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		/* ファイル名は指定。環境は継承 */
		if (execlp("./echoall", "echoall", "only 1 arg", (char *)0) < 0)
		{
			err_sys("execlp error");
		}
	}
	return (0);
}
