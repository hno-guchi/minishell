/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 17:51:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_wait_status(pid_t last_pid, int *last_pid_status,
		pid_t wait_pid, int wait_status)
{
	int	catch_signal_number;

	catch_signal_number = 0;
	if (wait_pid == last_pid)
	{
		if (WIFSIGNALED(wait_status))
		{
			catch_signal_number = WTERMSIG(wait_status);
			*last_pid_status = 128 + catch_signal_number;
		}
		else
			*last_pid_status = WEXITSTATUS(wait_status);
	}
	else
	{
		if (WIFSIGNALED(wait_status))
		{
			catch_signal_number = WTERMSIG(wait_status);
		}
	}
	return (catch_signal_number);
}

static void	putstr_signal(const int signal, const int last_pid_status)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (signal == SIGQUIT)
	{
		if (last_pid_status == 0)
		{
			ft_putchar_fd(' ', STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		}
	}
}

static int	wait_pipeline(pid_t last_pid)
{
	int		last_pid_status;
	int		wait_result_status;
	int		catch_signal_number;
	pid_t	wait_result_pid;

	last_pid_status = 0;
	wait_result_status = 0;
	catch_signal_number = 0;
	while (1)
	{
		wait_result_pid = wait(&wait_result_status);
		if (wait_result_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			else
				fatal_error("wait");
		}
		else
			catch_signal_number = check_wait_status(last_pid,
					&last_pid_status, wait_result_pid, wait_result_status);
	}
	if (0 < catch_signal_number)
		putstr_signal(catch_signal_number, last_pid_status);
	return (last_pid_status);
}

int	interpret(t_node *node)
{
	int		status;
	int		input_pipe[2];
	pid_t	last_pid;

	status = 0;
	input_pipe[0] = STDIN_FILENO;
	input_pipe[1] = -1;
	last_pid = exec_pipeline(node, input_pipe);
	status = wait_pipeline(last_pid);
	return (status);
}
