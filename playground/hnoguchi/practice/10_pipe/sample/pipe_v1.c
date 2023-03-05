/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:03:58 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/23 17:29:42 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(t_node *node)
{
	// if (node->next == NULL)
	// {
	// 	return ;
	// }
	if (pipe(node->pipe_fd) < 0)
	{
		fatal_error("prepare_pipe : pipe");
	}
	print_result_prepare_pipe(node);
}

void	prepare_pipe_child(t_node *node, int *prev_fd)
{
	print_before_prepare_pipe_child(node, prev_fd);
	if (prev_fd[0] != STDIN_FILENO)
	{
		// dprintf(STDERR_FILENO, "===== if (prev_fd[0] != STDIN_FILENO) =====\n");
		if (close(STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child : close 1");
		}
		// dprintf(STDERR_FILENO, "close(STDIN_FILENO);\n");
		if (dup2(prev_fd[0], STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child : dup2");
		}
		// dprintf(STDERR_FILENO, "dup2(prev_fd[0], STDIN_FILENO);\n");
		if (close(prev_fd[0]) < 0)
		{
			fatal_error("prepare_pipe_child : close 2");
		}
		// dprintf(STDERR_FILENO, "close(prev_fd[0]);\n");
		// dprintf(STDERR_FILENO, "=========================================\n\n");
	}
	if (close(node->pipe_fd[0]) < 0)
	{
		fatal_error("prepare_pipe_child : close 3");
	}
	// dprintf(STDERR_FILENO, "close(node->pipe_fd[0]); [%d]\n", node->pipe_fd[0]);
	if (node->next != NULL)
	{
		if (node->pipe_fd[1] != STDOUT_FILENO)
		{
			if (close(STDOUT_FILENO) < 0)
			{
				fatal_error("prepare_pipe_child : close 4");
			}
			// dprintf(STDERR_FILENO, "close(STDOUT_FILENO);\n");
			if (dup2(node->pipe_fd[1], STDOUT_FILENO) < 0)
			{
				fatal_error("prepare_pipe_child : dup2");
			}
			// dprintf(STDERR_FILENO, "dup2(node->pipe_fd[1], STDOUT_FILENO);\n");
		}
	}
	if (close(node->pipe_fd[1]) < 0)
	{
		fatal_error("prepare_pipe_child : close 5");
	}
	// dprintf(STDERR_FILENO, "close(node->pipe_fd[1]); [%d]\n", node->pipe_fd[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	// dprintf(STDERR_FILENO, "===== Parent =====\n");
	if (close(node->pipe_fd[1]) < 0)
	{
		fatal_error("prepare_pipe_parent : close");
	}
	// dprintf(STDERR_FILENO, "close(node->pipe_fd[1]); [%d]\n", node->pipe_fd[1]);
	// dprintf(STDERR_FILENO, "===================\n\n");
}
