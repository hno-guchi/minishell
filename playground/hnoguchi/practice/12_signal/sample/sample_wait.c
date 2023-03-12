/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:45:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/12 20:04:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

static void	signal_default(int signal)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal, &sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}

static pid_t	exec(void)
{
	pid_t	pid;
	extern char	**environ;
	char	*path = "/bin/cat";
	char	*argv[] = {
		"/bin/cat",
		NULL
	};
	pid = fork();
	if (pid < 0)
	{
		fatal_error("fork");
	}
	else if (pid == 0)
	{
		signal_default(SIGINT);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	return (pid);
}

static int	wait_pid(pid_t last_pid)
{
	int		status;
	int		status_location;
	int		signal_number;
	pid_t	wait_pid;

	status = 0;
	status_location = 0;
	signal_number = 0;
	while (1)
	{
		wait_pid = wait(&status_location);
		if (wait_pid != last_pid)
		{
			continue ;
		}
		if (WIFEXITED(status_location))
		{
			// dprintf(STDERR_FILENO, "WIFEXITED(); == true;\n");
			status = WEXITSTATUS(status_location);
			break ;
		}
		else if (WIFSIGNALED(status_location))
		{
			// dprintf(STDERR_FILENO, "WIFSIGNALED(); == true;\n");
			signal_number = WTERMSIG(status_location);
			if (signal_number == SIGINT)
			{
				dprintf(STDERR_FILENO, "catch SIGINT\n");
			}
			status = 128 + signal_number;
			break ;
		}
		else
		{
			fatal_error("wait");
		}
	}
	if (signal_number == SIGINT)
	{
		dprintf(STDERR_FILENO, "status == [%d]\n\n", status);
	}
	return (status);
}

static void	signal_ignore(int signal)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal, &sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}

int	main(void)
{
	pid_t	last_pid;
	int		status;

	while (1)
	{
		signal_ignore(SIGINT);
		last_pid = exec();
		status = wait_pid(last_pid);
	}
	return (status);
}
