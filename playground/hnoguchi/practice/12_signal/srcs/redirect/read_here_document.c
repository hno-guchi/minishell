/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_document.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/09 19:38:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static bool	is_break(char *line, t_token *token)
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

static void	read_until_delimiter(t_token *token, int *pipe_fd)
{
	char	*line;

	line = NULL;
	g_minishell.readline_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (is_break(line, token))
		{
			break ;
		}
		if (write(pipe_fd[1], line, ft_strlen(line)) < 0)
		{
			fatal_error("write");
		}
		if (write(pipe_fd[1], "\n", 1) < 0)
		{
			fatal_error("write");
		}
		free(line);
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
