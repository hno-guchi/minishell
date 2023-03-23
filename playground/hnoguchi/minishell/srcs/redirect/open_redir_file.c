/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/23 12:02:49 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_open_file(t_token *token, int flags, mode_t mode)
{
	token->file_fd = open(token->word, flags, mode);
	if (token->file_fd < 0)
	{
		xperror(token->word);
		return (-1);
	}
	token->file_fd = stash_fd(token->file_fd);
	return (0);
}

static int	open_redir_in(t_token *token)
{
	while (token != NULL)
	{
		if (token->redir_kind == REDIR_IN)
		{
			if (do_open_file(token, O_RDONLY, 0644) < 0)
				return (-1);
		}
		else if (token->redir_kind == REDIR_HERE_DOC)
		{
			if (read_here_document(token) < 0)
				return (-1);
		}
		else if (token->redir_kind == REDIR_EXPAND_HERE_DOC)
		{
			if (read_here_document(token) < 0)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}

static int	open_redir_out(t_token *token)
{
	while (token != NULL)
	{
		if (token->redir_kind == REDIR_OUT)
		{
			if (do_open_file(token, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
			{
				return (-1);
			}
		}
		else if (token->redir_kind == REDIR_APPEND_OUT)
		{
			if (do_open_file(token, O_WRONLY | O_CREAT | O_APPEND, 0644) < 0)
			{
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	open_redir_file(t_node *node)
{
	t_node	*redir;

	redir = NULL;
	if (node == NULL)
		return (0);
	while (node != NULL)
	{
		redir = node->command->redirects;
		while (redir != NULL)
		{
			if (redir->kind == NODE_REDIR_IN)
			{
				if (open_redir_in(redir->args) < 0)
					return (-1);
			}
			else if (redir->kind == NODE_REDIR_OUT)
			{
				if (open_redir_out(redir->args) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		node = node->next;
	}
	return (0);
}
