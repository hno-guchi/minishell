/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/26 22:59:29 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *command)
{
	if (command == NULL)
	{
		fatal_error("is_builtin");
	}
	else if (ft_strcmp(command, "echo") == 0)
		return (true);
	else if (ft_strcmp(command, "cd") == 0)
		return (true);
	else if (ft_strcmp(command, "pwd") == 0)
		return (true);
	else if (ft_strcmp(command, "export") == 0)
		return (true);
	else if (ft_strcmp(command, "unset") == 0)
		return (true);
	else if (ft_strcmp(command, "env") == 0)
		return (true);
	else if (ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}

int	interpret(t_node *node)
{
	int		status;
	int		input_pipe[2];
	pid_t	last_pid;

	status = 0;
	input_pipe[0] = STDIN_FILENO;
	input_pipe[1] = -1;
	if (node->command->args == NULL)
	{
		return (0);
	}
	if (node->next == NULL && is_builtin(node->command->args->word))
	{
		status = exec_builtin(node);
	}
	else
	{
		last_pid = exec_pipeline(node, input_pipe);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
