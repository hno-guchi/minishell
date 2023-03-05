#include "my_popen.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
 * 実行時に割り付ける配列へのポインタ
 */
static pid_t	*childpid = NULL;

/*
 * 自前のopen_max();で取得
 */
static int	maxfd;

FILE	*my_popen(const char *cmdstring, const char *type)
{
	int		i;
	int		pfd[2];
	pid_t	pid;
	FILE	*fp;

	/* "r" か "w" のみ許可 */
	if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0)
	{
		errno = EINVAL;
		return (NULL);
	}
	/* 最初は、ここを通る */
	if (childpid == NULL)
	{
		/* 子のPIDを納めるゼロクリアした配列を割り付ける */
		maxfd = open_max();
		if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
		{
			return (NULL);
		}
	}
	if (pipe(pfd) < 0)
	{
		/* pipe()が設定したエラー */
		return (NULL);
	}
	if (maxfd <= pfd[0] || maxfd <= pfd[1])
	{
		close(pfd[0]);
		close(pfd[1]);
		errno = EMFILE;
		return (NULL);
	}
	if ((pid = fork()) < 0)
	{
		/* fork()が設定したエラー */
		return (NULL);
	}
	else if (pid == 0)
	{
		/* child */
		if (*type == 'r')
		{
			close(pfd[0]);
			if (pfd[1] != STDOUT_FILENO)
			{
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[0]);
			}
		}
		else
		{
			close(pfd[1]);
			if (pfd[0] != STDIN_FILENO)
			{
				dup2(pfd[0], STDIN_FILENO);
				close(pfd[0]);
			}
		}
		/* childpid[]内のすべての記述子をクローズする */
		for (i = 0; i < maxfd; i++)
		{
			if (0 < childpid[1])
			{
				close(i);
			}
		}
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	}

	/* 親側は続行。。。 */
	if (*type == 'r')
	{
		close(pfd[1]);
		if ((fp = fdopen(pfd[0], type)) == NULL)
		{
			return (NULL);
		}
	{
	else
	{
		close(pfd[0]);
		if ((fp = fdopen(pfd[1], type)) == NULL)
		{
			return (NULL);
		}
	}
	/* この記述子の子のPIDを記録 */
	childpid[fileno(fp)] = pid;
	return (fp);
}

int	my_pclose(FILE *fp)
{
	int		fd;
	int		stat;
	pid_t	pid;

	if (childpid == NULL)
	{
		errno = EINVAL;
		/* popen(); が呼ばれていない */
		return (-1);
	}
	fd = fileno(fp);
	if (maxfd <= fd)
	{
		errno = EINVAL;
		/* 不正なファイル記述子 */
		return (-1);
	}
	if ((pid = childpid[fd]) == 0)
	{
		errno = EINVAL;
		/* popen();がオープンしたfpではない */
		return (-1);
	}
	childpid[fd] = 0;
	if (fclose(fp) == EOF)
	{
		return (-1);
	}
	while (waitpid(pid, &stat, 0) < 0)
	{
		if (errno != EINTR)
		{
			/* waitpid() のEINTR以外のエラー */
			return (-1);
		}
	}
	/* 子の終了状態を返す */
	return (stat);
}
