/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 14:51:07 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_wstatus(int *status, int wstatus)
{
	if (WIFSIGNALED(wstatus))
	{
		*status = 128 + WTERMSIG(wstatus);
	}
	else
	{
		*status = WEXITSTATUS(wstatus);
	}
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	status = 0;
	wstatus = 0;
	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			check_wstatus(&status, wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

int	interpret(t_node *node)
{
	int		status;
	int		pipe_fd[2];
	pid_t	last_pid;

	status = 0;
	pipe_fd[0] = STDIN_FILENO;
	pipe_fd[1] = STDOUT_FILENO;
	last_pid = exec_pipeline(node, pipe_fd);
	dprintf(STDERR_FILENO, "last_pid = [%d];\n", last_pid);
	status = wait_pipeline(last_pid);
	return (status);
}
