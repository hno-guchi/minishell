/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:03:58 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 12:16:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		fatal_error("pipe");
	}
}

void	connect_pipe_fd(int male, int female)
{
	if (close(female) < 0)
	{
		fatal_error("close");
	}
	if (dup2(male, female) < 0)
	{
		fatal_error("dup2");
	}
}

void	prepare_pipe_child(t_node *node, int *pipe_fd, int *prev_fd)
{
	if (prev_fd[0] != STDIN_FILENO)
	{
		connect_pipe_fd(prev_fd[0], STDIN_FILENO);
		if (close(prev_fd[0]) < 0)
		{
			fatal_error("close");
		}
	}
	if (close(pipe_fd[0]) < 0)
	{
		fatal_error("close");
	}
	if (node->next != NULL)
	{
		if (pipe_fd[1] != STDOUT_FILENO)
		{
			connect_pipe_fd(pipe_fd[1], STDOUT_FILENO);
		}
	}
	if (close(pipe_fd[1]) < 0)
	{
		fatal_error("close");
	}
}

void	prepare_pipe_parent(int *pipe_fd)
{
	if (pipe_fd[1] != STDOUT_FILENO)
	{
		if (close(pipe_fd[1]) < 0)
		{
			fatal_error("prepare_pipe_parent : close");
		}
	}
}
