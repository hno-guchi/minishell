/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/14 16:07:50 by hnoguchi         ###   ########.fr       */
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
	if (token->kind != TK_WORD)
	{
		return ;
	}
	token->file_fd = open(token->word, flags, mode);
	if (token->file_fd == -1)
	{
		fatal_error("open_redirect_file: open()");
	}
	token->file_fd = stash_fd(token->file_fd);
}

void	open_redir_in(t_token *token)
{
	while (token != NULL)
	{
		if (token->kind == TK_WORD)
		{
			open_redirect_file(token, O_RDONLY, 0644);
		}
		token = token->next;
	}
}

void	open_redir_out(t_token *token)
{
	while (token != NULL)
	{
		if (token->kind == TK_OPERATOR)
		{
			if (strcmp(token->word, ">>") == 0)
			{
				token = token->next;
				open_redirect_file(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else if (strcmp(token->word, ">") == 0)
			{
				token = token->next;
				open_redirect_file(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
		}
		token = token->next;
	}
}

void	do_redirect(t_fd *fd, t_token *token)
{
	while (token != NULL)
	{
		if (token->kind == TK_OPERATOR)
		{
			token = token->next;
			continue ;
		}
		if (token->file_fd != fd->target)
		{
			token->stashed_file_fd = stash_fd(fd->target);
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
	}
}

void	do_print_result_redir(t_token *token)
{
	if (token->kind == TK_OPERATOR)
	{
		dprintf(STDERR_FILENO, "\ntoken->word          : [%s]\n\n", token->word);
	}
	if (token->kind == TK_WORD)
	{
		dprintf(STDERR_FILENO, "token->word            : [%s]\n", token->word);
		dprintf(STDERR_FILENO, "token->file_fd         : [%d]\n", token->file_fd);
		dprintf(STDERR_FILENO, "token->stashed_file_fd : [%d]\n", token->stashed_file_fd);
	}
}

void	print_result_open_redir(t_token *token, char *message)
{
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, GREEN"%s"END, message);
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, "----------------------------------------\n");
	while (token != NULL)
	{
		do_print_result_redir(token);
		token = token->next;
	}
	dprintf(STDERR_FILENO, "----------------------------------------\n");
}

void	print_result_close_redir(t_token *token, char *message)
{
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, RED"%s"END, message);
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, "----------------------------------------\n");
	do_print_result_redir(token);
	dprintf(STDERR_FILENO, "----------------------------------------\n");
}

void	redirect(t_node *node)
{
	t_node	*redir;

	redir = node->redirects;
	if (node == NULL || redir == NULL)
	{
		return ;
	}
	while (redir != NULL)
	{
		if (redir->kind == NODE_REDIR_IN)
		{
			open_redir_in(redir->args);
			print_result_open_redir(redir->args, "[AFTER] : open_redir_in();");
			do_redirect(&node->input_fd, redir->args);
			print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			open_redir_out(redir->args);
			print_result_open_redir(redir->args, "[AFTER] : open_redir_out();");
			do_redirect(&node->output_fd, redir->args);
			print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		redir = redir->next;
	}
}

void	close_redirect_file(int *target, t_token *token)
{
	if (token == NULL)
	{
		return ;
	}
	close_redirect_file(target, token->next);
	if (token->kind == TK_OPERATOR)
	{
		return ;
	}
	print_result_close_redir(token, "[EXECUTE] close_redirect_file();");
	if (close(*target) < 0)
	{
		fatal_error("close_redirect_file: close(*target_fd);");
	}
	if (dup2(token->stashed_file_fd, *target) < 0)
	{
		fatal_error("close_redirect_file: dup2();");
	}
	if (close(token->stashed_file_fd) < 0)
	{
		fatal_error("close_redirect_file: close(stashed_file_fd);");
	}
	// if (close(fd->target) < 0)
	// {
	// 		fatal_error("reset_redirect: close();");
	// }
}

void	reset_redirect(t_node *node)
{
	t_node	*redir;

	redir = node->redirects;
	if (node == NULL || redir == NULL)
	{
		return ;
	}
	while (redir != NULL)
	{
		if (redir->kind == NODE_REDIR_IN)
		{
			close_redirect_file(&node->input_fd.target, redir->args);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			close_redirect_file(&node->output_fd.target, redir->args);
		}
		redir = redir->next;
	}
}
