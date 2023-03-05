/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 16:32:24 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirect(int *target_fd, t_token *args)
{
	if (args == NULL)
	{
		return ;
	}
	while (args != NULL)
	{
		if (args->kind == TK_OPERATOR)
		{
			args = args->next;
			continue ;
		}
		if (args->file_fd != *target_fd)
		{
			args->stashed_file_fd = stash_fd(*target_fd);
			if (dup2(args->file_fd, *target_fd) < 0)
			{
				fatal_error("dup2");
			}
			if (close(args->file_fd) < 0)
			{
				fatal_error("close");
			}
		}
		args = args->next;
	}
}

void	redirect_file(t_node *command)
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
			do_redirect(&command->input_fd, redir->args);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			do_redirect(&command->output_fd, redir->args);
		}
		redir = redir->next;
	}
}
