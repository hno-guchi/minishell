/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/08 17:25:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

# define ERROR_PREFIX "minishell: "

bool	g_syntax_error = false;

bool	at_eof(t_token_kind kind)
{
	return (kind == TK_EOF);
}

static void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	tokenize_error(char *location, char **rest, char *line)
{
	g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected character `%c' in %s\n", *line, location);
	while (*line)
	{
		line++;
	}
	*rest = line;
}

/*
void	fatal_error(const char *message)
{
	// TODO: change function dprintf() -> ft_putstr_fd();
	perror_prefix();
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", message);
	exit(1);
}
*/

void	error_message(const char *location, const char *message, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s", location, message);
	exit(status);
}

void	assert_error(const char *message)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Assert Error: %s\n", message);
	exit (255);
}

void	error_exit(const char *location, const char *message, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s\n", location, message);
	exit (status);
}

/*
void	todo(const char *message)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "TODO: %s\n", message);
	exit(255);
}
*/

void	parse_error(const char *location, t_token **rest, t_token *token)
{
	g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected token `%s' in %s\n", token->word, location);
	while (token && !at_eof(token->kind))
	{
		token = token->next;
	}
	*rest = token;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
