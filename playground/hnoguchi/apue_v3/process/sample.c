/*
 * #include <unistd.h>
 * pid_t	fork(void);
 *
 * create a new process
 *
 * DESCRIPTION
 * The function causes creation of a new process.
 * The new process (child process) is an exact copy of the calling process (parent process) except for the following:
 * 	- The child process has a unique process ID.
 * 	- The child process has a different parent process ID.
 * 	  (i.e., the process ID of the parent process).
 *  ~~~
 *
 * RETURN VALUES
 * Upon successful completion, fork() returns a value of 0 to the child process and returns the process ID of the child process to the parent process.
 *
 *
 *
 * #include <unistd.h>
 * int	execve(const char *path, char *const argv[], char *const envp[]);
 *
 * Execute a file
 *
 * DESCRIPTION
 * The function transforms the calling process into a new process.
 * The new process is constructed from an ordinary file, whose name is pointed to by [path], called the [new process file].
 *
 *
 *
 * #include <sys/types.h> (The include file is necessary.)
 * #include <sys/wait.h>
 * pid_t	wait(int *stat_loc);
 *
 * wait for process termination
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		fprintf(stderr, "fork(2) failed\n");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "fork(2) failed\n");
		exit(1);
	}
	if (pid == 0)
	{
		/* Child process */
		execl(argv[1], argv[1], argv[2], NULL);
		/* execl()が呼び出しから戻ったら失敗 */
		perror(argv[1]);
		exit(99);
	}
	else
	{
		/* Parent process */
		int	status;

		waitpid(pid, &status, 0);
		printf("child (PID=%d) finished; ", pid);
		if (WIFEXITED(status))
		{
			printf("exit, status=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("signal, sig=%d\n", WTERMSIG(status));
		}
		else
		{
			printf("abnormal exit\n");
		}
	}
	exit(0);
}
