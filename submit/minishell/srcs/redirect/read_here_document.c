/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_document.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/23 11:49:25 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_delimiter(char *line, t_token *token)
{
	if (line == NULL)
	{
		return (true);
	}
	if (g_minishell.readline_interrupted == true)
	{
		return (true);
	}
	if (ft_strcmp(line, token->word) == 0)
	{
		return (true);
	}
	return (false);
}

static void	write_line_to_pipe(char *line, int fd)
{
	if (line != NULL)
	{
		if (write(fd, line, ft_strlen(line)) < 0)
		{
			fatal_error("write");
		}
	}
	if (write(fd, "\n", 1) < 0)
	{
		fatal_error("write");
	}
}

static void	write_expand_parameter(char *current_line, int fd)
{
	char	*line_expanded;

	line_expanded = NULL;
	while (*current_line != '\0')
	{
		if (is_variable(current_line))
		{
			append_variable(&line_expanded, &current_line, current_line);
		}
		else if (is_special_parameter(current_line))
		{
			append_special_param(&line_expanded, &current_line, current_line);
		}
		else
		{
			add_character(&line_expanded, *current_line);
			current_line++;
		}
	}
	write_line_to_pipe(line_expanded, fd);
	free(line_expanded);
}

static void	read_until_delimiter(t_token *token, int *pipe_fd)
{
	char	*line;

	line = NULL;
	g_minishell.readline_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (is_delimiter(line, token))
		{
			break ;
		}
		if (token->redir_kind == REDIR_HERE_DOC)
		{
			write_expand_parameter(line, pipe_fd[1]);
		}
		else
		{
			write_line_to_pipe(line, pipe_fd[1]);
		}
		free(line);
		line = NULL;
	}
	if (line != NULL)
		free(line);
}

int	read_here_document(t_token *token)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		fatal_error("pipe");
	}
	read_until_delimiter(token, pipe_fd);
	if (close(pipe_fd[1]) < 0)
	{
		fatal_error("close");
	}
	if (g_minishell.readline_interrupted == true)
	{
		if (close(pipe_fd[0]) < 0)
		{
			fatal_error("close");
		}
		return (-1);
	}
	token->file_fd = stash_fd(pipe_fd[0]);
	return (0);
}
