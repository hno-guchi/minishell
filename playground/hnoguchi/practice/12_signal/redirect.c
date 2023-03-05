/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 12:06:09 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

int	do_open_file(t_token *token, int flags, mode_t mode)
{
	if (token->kind != TK_WORD)
	{
		return (0);
	}
	token->file_fd = open(token->word, flags, mode);
	if (token->file_fd == -1)
	{
		xperror(token->word);
		return (-1);
	}
	token->file_fd = stash_fd(token->file_fd);
	return (0);
}

void	read_here_document(t_token *token)
{
	int		pipe_fd[2];
	char	*line;

	line = NULL;
	if (pipe(pipe_fd) == -1)
	{
		fatal_error("read_here_document: pipe()");
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if (strcmp(line, token->word) == 0)
		{
			free(line);
			break ;
		}
		if (write(pipe_fd[1], line, strlen(line)) == -1)
		{
			fatal_error("read_here_document: write() 1");
		}
		if (write(pipe_fd[1], "\n", 1) == -1)
		{
			fatal_error("read_here_document: write() 2");
		}
		free(line);
	}
	if (close(pipe_fd[1]) == -1)
	{
		fatal_error("read_here_document: close()");
	}
	token->file_fd = stash_fd(pipe_fd[0]);
}

int	open_redir_in(t_token *token)
{
	while (token != NULL)
	{
		if (token->kind == TK_OPERATOR)
		{
			if (strcmp(token->word, "<") == 0)
			{
				token = token->next;
				if (do_open_file(token, O_RDONLY, 0644) < 0)
				{
					// closes_fd();
					return (-1);
				}
			}
			else if (strcmp(token->word, "<<") == 0)
			{
				token = token->next;
				read_here_document(token);
			}
		}
		token = token->next;
	}
	return (0);
}

int	open_redir_out(t_token *token)
{
	while (token != NULL)
	{
		if (token->kind == TK_OPERATOR)
		{
			if (strcmp(token->word, ">>") == 0)
			{
				token = token->next;
				if (do_open_file(token, O_WRONLY | O_CREAT | O_APPEND, 0644))
				{
					// closes_fd();
					return (-1);
				}
			}
			else if (strcmp(token->word, ">") == 0)
			{
				token = token->next;
				if (do_open_file(token, O_WRONLY | O_CREAT | O_TRUNC, 0644))
				{
					// closes_fd();
					return (-1);
				}
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
	{
		return (0);
	}
	while (node != NULL)
	{
		redir = node->command->redirects;
		while (redir != NULL)
		{
			if (redir->kind == NODE_REDIR_IN)
			{
				if (open_redir_in(redir->args) < 0)
				{
					// closes_fd();
					return (-1);
				}
				// print_result_open_redir(redir->args, "[AFTER] : open_redir_in();");
			}
			else if (redir->kind == NODE_REDIR_OUT)
			{
				if (open_redir_out(redir->args) < 0)
				{
					// closes_fd();
					return (-1);
				}
				// print_result_open_redir(redir->args, "[AFTER] : open_redir_out();");
			}
			redir = redir->next;
		}
		node = node->next;
	}
	return (0);
}

void	do_redirect(int *target_fd, t_token *args)
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
				fatal_error("do_redirect: dup2();");
			}
			if (close(args->file_fd) < 0)
			{
				fatal_error("do_redirect: close();");
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
			// print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			do_redirect(&command->output_fd, redir->args);
			// print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		redir = redir->next;
	}
}

void	close_redirect_file(int *target_fd, t_token *token)
{
	if (token == NULL)
	{
		return ;
	}
	close_redirect_file(target_fd, token->next);
	if (token->kind == TK_OPERATOR)
	{
		return ;
	}
	// print_result_close_redir(target_fd, token, "[EXECUTE] close_redirect_file();");
	if (close(*target_fd) < 0)
	{
		assert_error("close_redirect_file: close(*target_fd);");
	}
	if (dup2(token->stashed_file_fd, *target_fd) < 0)
	{
		assert_error("close_redirect_file: dup2();");
	}
	if (close(token->stashed_file_fd) < 0)
	{
		assert_error("close_redirect_file: close(stashed_file_fd);");
	}
	if (close(token->file_fd) < 0)
	{
		assert_error("close_redirect_file: close(target_fd);");
	}
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

void	closes_file(t_token *args)
{
	if (args == NULL)
	{
		return ;
	}
	while (args != NULL)
	{
		if (args->kind == TK_WORD)
		{
			if (close(args->file_fd) < 0)
			{
				assert_error("closes_file: close(args->file_fd);");
			}
		}
		args = args->next;
	}
}

void	close_target_command(t_node *command)
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
			closes_file(redir->args);
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			closes_file(redir->args);
		}
		redir = redir->next;
	}
}

void	closes_redirect_file(t_node *node)
{
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		close_target_command(node->command);
		node = node->next;
	}
}

/*
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
			// print_result_open_redir(redir->args, "[AFTER] : open_redir_in();");
			do_redirect(&node->input_fd, redir->args);
			// print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		else if (redir->kind == NODE_REDIR_OUT)
		{
			open_redir_out(redir->args);
			// print_result_open_redir(redir->args, "[AFTER] : open_redir_out();");
			do_redirect(&node->output_fd, redir->args);
			// print_result_open_redir(redir->args, "[AFTER] : do_redirect();");
		}
		redir = redir->next;
	}
}
*/


