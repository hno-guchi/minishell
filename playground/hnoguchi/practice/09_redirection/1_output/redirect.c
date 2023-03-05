/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/09 19:15:15 by hnoguchi         ###   ########.fr       */
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

void	open_redirect_file(t_node *node)
{
	t_node	*redir;

	redir = node->redirects;
	while (redir != NULL)
	{
		redir->target_fd = open(redir->args->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redir->target_fd == -1)
		{
			fatal_error("open_redirect_file: open()");
		}
		redir->stashed_target_fd = stash_fd(redir->target_fd);
		redir = redir->next;
	}
}

void	do_redirect(t_node *node)
{
	t_node	*redir;

	redir = node->redirects;
	while (redir != NULL)
	{
		node->stashed_target_fd = stash_fd(node->target_fd);
		if (redir->stashed_target_fd != node->target_fd)
		{
			if (dup2(redir->stashed_target_fd, node->target_fd) < 0)
			{
				fatal_error("do_redirect: dup2();");
			}
			if (close(redir->stashed_target_fd) < 0)
			{
				fatal_error("do_redirect: close();");
			}
		}
		redir = redir->next;
	}
}

void	redirect(t_node *node)
{
	if (node == NULL || node->redirects == NULL)
	{
		return ;
	}
	open_redirect_file(node);
	do_redirect(node);
}

void	reset_redirect(t_node *node)
{
	if (dup2(node->stashed_target_fd, node->target_fd) < 0)
	{
			fatal_error("reset_redirect: dup2();");
	}
	if (close(node->stashed_target_fd) < 0)
	{
			fatal_error("reset_redirect: close();");
	}
	// if (close(node->target_fd) < 0)
	// {
	// 		fatal_error("reset_redirect: close();");
	// }
}
