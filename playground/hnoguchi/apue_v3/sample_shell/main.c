#include "main.h"
#include "err_func.h"

int	main(void)
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	/* プロンプトの表示 */
	printf("minishell$ ");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
		{
			/* 改行文字をnullに置換 */
			buf[strlen(buf) - 1] = 0;
		}
		if ((pid = fork()) < 0)
		{
			err_sys("fork error");
		}
		else if (pid == 0)
		{
			/* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}
		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
		{
			err_sys("waitpid error");
		}
		printf("minishell$ ");
	}
	exit (0);
}
