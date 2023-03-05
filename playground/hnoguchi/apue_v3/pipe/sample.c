/*
 * ペイジェープログラムへファイルをコピー
 */

#include "sample.h"

int	main(int argc, char **argv)
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager;
	char	*argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2)
	{
		err_quit("usage: a.out <pathname>");
	}

	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		err_sys("can't open %s", argv[1]);
	}
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
		/* 読み取り端点をcloseする */
		close(fd[0]);
		/* 親はargv[1];をパイプへコピー */
		while (fgets(line, MAXLINE, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
			{
				err_sys("write error to pipe");
			}
		}
		if (ferror(fp))
		{
			err_sys("fgets error");
		}
		/* 読み手側のパイプの書き出し端点をクローズする */
		close(fd[1]);
		if (waitpid(pid, NULL, 0) < 0)
		{
			err_sys("waitpid error");
		}
		exit(0);
	}
	else
	{
		/* child */
		/* 書き出し端点をクローズする */
		close (fd[1]);
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
			{
				err_sys("dup2 error to stdin");
			}
			/* dup2の後でこれは必要ない */
			close(fd[0]);
		}

		/* execl(); の引数を取得 */
		if ((pager = getenv("PAGER")) == NULL)
		{
			pager = DEF_PAGER;
		}
		
		if ((argv0 = strrchr(pager, '/')) != NULL)
		{
			/* 最右端のスラッシュの次 */
			argv0++;
		}
		else
		{
			/* ペイジャーにスラッシュがない */
			argv0 = pager;
		}

		if (execl(pager, argv0, (char *)0) < 0)
		{
			err_sys("execl error for %s", pager);
		}
	}
	exit (0);
}
