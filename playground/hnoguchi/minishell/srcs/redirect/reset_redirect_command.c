/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redirect_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/23 12:04:51 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_redirect_file(int *target_fd, t_token *args)
{
	if (args == NULL)
	{
		return ;
	}
	close_redirect_file(target_fd, args->next);
	reset_close(target_fd);
	if (dup2(args->stashed_file_fd, *target_fd) < 0)
	{
		fatal_error("dup2");
	}
	reset_close(&args->stashed_file_fd);
	reset_close(&args->file_fd);
}

void	reset_redirect_command(t_node *command)
{
	t_node	*redir;

	redir = NULL;
	if (command == NULL)
	{
		return ;
	}
	redir = command->redirects;
	while (redir != NULL)
	{
		if (redir->kind == NODE_REDIR_IN)
		{
			close_redirect_file(&command->input_fd, redir->args);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			close_redirect_file(&command->output_fd, redir->args);
		}
		redir = redir->next;
	}
}
