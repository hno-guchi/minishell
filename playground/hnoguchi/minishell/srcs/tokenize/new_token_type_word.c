/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_type_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 20:57:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_break(char c)
{
	if (is_blank(c))
	{
		return (true);
	}
	else if (is_meta_character(c))
	{
		return (true);
	}
	return (false);
}

static void	error_unclose_quote(char **rest, char *line, char quote,
		char last_c)
{
	if (quote == SINGLE_QUOTE_CHAR)
	{
		tokenize_error("Unclosed single quote", rest, line, last_c);
	}
	else if (quote == DOUBLE_QUOTE_CHAR)
	{
		tokenize_error("Unclosed double quote", rest, line, last_c);
	}
	return ;
}

static void	increment_until_quote(char **rest, char *line, char quote)
{
	char	last_character;

	last_character = *line;
	line++;
	while (*line != quote)
	{
		if (*line == '\0')
		{
			return (error_unclose_quote(rest, line, quote, last_character));
		}
		last_character = *line;
		line++;
	}
	if (*line == quote)
	{
		line++;
	}
	*rest = line;
}

t_token	*new_token_type_word(char **rest, char *line)
{
	const char	*start_p;
	char		*word;

	start_p = line;
	word = NULL;
	while (*line != '\0')
	{
		if (is_break(*line))
			break ;
		else if (*line == SINGLE_QUOTE_CHAR || *line == DOUBLE_QUOTE_CHAR)
			increment_until_quote(&line, line, *line);
		else
			line++;
	}
	word = ft_strndup(start_p, line - start_p);
	if (word == NULL)
		fatal_error("strndup");
	else
	{
		*rest = line;
		return (new_token(TK_WORD, word));
	}
	tokenize_error("Unexpected Token", &line, line, *line);
	return (NULL);
}
