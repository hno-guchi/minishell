/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:52:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/17 14:48:28 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Single pipeline
 * ~$ ls | wc -l
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	fatal_error(char *location, char *message)
{
	dprintf(STDERR_FILENO, "%s: %s\n", location, message);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) < 0)
	{
		fatal_error("main", "pipe");
	}
	pid = fork();
	if (pid < 0)
	{
		fatal_error("main", "fork");
	}
	else if (pid == 0)
	{
		/* child process */
		if (close(pipe_fd[0]) < 0)
		{
			fatal_error("main", "close 0");
		}
		if (pipe_fd[1] != STDOUT_FILENO)
		{
			if (close(STDOUT_FILENO) < 0)
			{
				fatal_error("main", "close out");
			}
			if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			{
				fatal_error("main", "dup2");
			}
			if (close(pipe_fd[1]) < 0)
			{
				fatal_error("main", "close 1");
			}
		}
		execlp("ls", "ls", (char *)NULL);
		fatal_error("main", "execlp");
	}
	/* Parent process */
	else
		;
	pid = fork();
	if (pid < 0)
	{
		fatal_error("main", "fork");
	}
	else if (pid == 0)
	{
		/* child process */
		if (close(pipe_fd[1]) < 0)
		{
			fatal_error("main", "close 1");
		}
		if (pipe_fd[0] != STDIN_FILENO)
		{
			if (close(STDIN_FILENO) < 0)
			{
				fatal_error("main", "close in");
			}
			if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			{
				fatal_error("main", "dup2");
			}
			if (close(pipe_fd[0]) < 0)
			{
				fatal_error("main", "close 0");
			}
		}
		execlp("wc", "wc", "-l", (char *)NULL);
		fatal_error("main", "execlp");
	}
	/* Parent process */
	else
		;
	if (close(pipe_fd[0]) < 0)
	{
		fatal_error("main", "close 0");
	}
	if (close(pipe_fd[1]) < 0)
	{
		fatal_error("main", "close 1");
	}
	if (wait(NULL) < 0)
	{
		fatal_error("main", "wait");
	}
	exit(EXIT_SUCCESS);
}
/*
	if (pipe_fd[0] != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) < 0)
		{
			fatal_error("main", "close 0");
		}
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		{
			fatal_error("main", "close");
		}
		if (close(pipe_fd[0]) < 0)
		{
			fatal_error("main", "close 1");
		}
	}
*/
