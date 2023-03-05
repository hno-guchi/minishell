/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/10 19:28:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "redirect.h"

static int	stash_fd(int fd)
{
	int	stash_fd;

	stash_fd = fcntl(fd, F_DUPFD, 10);
	if (stash_fd < 0)
	{
		fatal_error("fcntl");
	}
	if (close(fd) < 0)
	{
		fatal_error("close");
	}
	return (stash_fd);
}

void	open_redirect_file(t_token *token, int flags, mode_t mode)
{
	while (token != NULL)
	{
		token->file_fd = open(token->word, flags, mode);
		if (token->file_fd == -1)
		{
			fatal_error("open_redirect_file: open()");
		}
		token->file_fd = stash_fd(token->file_fd);
		token = token->next;
	}
}

void	do_redirect(t_fd *fd, t_token *token)
{
	ssize_t	count;

	count = 0;
	fd->stashed_target = stash_fd(fd->target);
	while (token != NULL)
	{
		if (token->file_fd != fd->target)
		{
			if (0 < count)
			{
				if (close(fd->target) < 0)
				{
					fatal_error("do_redirect: close(fd->target);");
				}
			}
			if (dup2(token->file_fd, fd->target) < 0)
			{
				fatal_error("do_redirect: dup2();");
			}
			if (close(token->file_fd) < 0)
			{
				fatal_error("do_redirect: close();");
			}
		}
		token = token->next;
		count += 1;
	}
}

void	redirect(t_node *node)
{
	t_node	*redir;

	if (node == NULL || node->redirects == NULL)
	{
		return ;
	}
	redir = node->redirects;
	while (redir != NULL)
	{
		if (redir->kind == NODE_REDIR_IN)
		{
			open_redirect_file(redir->args, O_RDONLY, 0644);
			do_redirect(&node->input_fd, redir->args);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			open_redirect_file(redir->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			do_redirect(&node->output_fd, redir->args);
		}
		redir = redir->next;
	}
}

void	close_redirect_file(t_fd *fd)
{
	if (close(fd->target) < 0)
	{
		fatal_error("reset_redirect: close();");
	}
	if (dup2(fd->stashed_target, fd->target) < 0)
	{
		fatal_error("reset_redirect: dup2();");
	}
	if (close(fd->stashed_target) < 0)
	{
		fatal_error("reset_redirect: close();");
	}
	// if (close(fd->target) < 0)
	// {
	// 		fatal_error("reset_redirect: close();");
	// }
}

void	reset_redirect(t_node *node)
{
	t_node	*redir;

	redir = NULL;
	if (node == NULL || node->redirects == NULL)
	{
		return ;
	}
	redir = node->redirects;
	while (redir != NULL)
	{
		if (redir->kind == NODE_REDIR_IN)
		{
			close_redirect_file(&node->input_fd);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			close_redirect_file(&node->output_fd);
		}
		redir = redir->next;
	}
}
