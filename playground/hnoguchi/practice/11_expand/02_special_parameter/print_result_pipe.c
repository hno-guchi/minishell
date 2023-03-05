/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:03:58 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 13:29:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_result_prepare_pipe(t_node *node)
{
	dprintf(STDERR_FILENO, "===== prepare_pipe(); =====\n");
	dprintf(STDERR_FILENO, "node->pipe_fd[0] : [%d]\n", node->pipe_fd[0]);
	dprintf(STDERR_FILENO, "node->pipe_fd[1] : [%d]\n", node->pipe_fd[1]);
	dprintf(STDERR_FILENO, "===========================\n\n");
}
*/

void	print_before_prepare_pipe_child(int *pipe_fd, int *prev_fd)
{
	dprintf(STDERR_FILENO, "== prepare_pipe_child(); ==\n");
	dprintf(STDERR_FILENO, "[BEFOR]\n");
	dprintf(STDERR_FILENO, "pipe_fd[0] : [%d]\n", pipe_fd[0]);
	dprintf(STDERR_FILENO, "pipe_fd[1] : [%d]\n", pipe_fd[1]);
	dprintf(STDERR_FILENO, "prev_fd[0]       : [%d]\n", prev_fd[0]);
	dprintf(STDERR_FILENO, "prev_fd[1]       : [%d]\n", prev_fd[1]);
	dprintf(STDERR_FILENO, "===========================\n\n");
}
