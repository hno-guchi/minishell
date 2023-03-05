/*
 * #include <sys/wait.h>
 * pid_t	waitpid(pid_t pid, int *stat_loc, int options);
 *
 * wait for process termination
 */


/* forkを２度呼びゾンビプロセスを避ける */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
	}
	else if (pid == 0)
	{
		/* first child */
		if ((pid = fork()) < 0)
		{
			fprintf(stderr, "fork error\n");
		}
		else if (0 < pid)
		{
			/* Parent of second child == first child */
			exit(0);
		}
		/*
		 * ここは、２番目の子：上の文で実の親がexit();を呼ぶと、
		 * 直ちにinitがparentになる。
		 * 以後、動作を続けるが、終了したらinitが状態を見てくれる。
		 */
		sleep(2);
		printf("second child, parent pid = [%ld]\n", (long)getppid());
		exit (0);
	}

	if (waitpid(pid, NULL, 0) != pid)
	{
		fprintf(stderr, "waitpid error\n");
	}
	/*
	 * ここは親（元のプロセス）。
	 * ２番目の子の親ではないので実行を続ける。
	 */
	return (0);
}
