/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_remove_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:55 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/26 22:58:26 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(char **new_word, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
	current_word++;
	while (*current_word != quote)
	{
		if (*current_word == '\0')
		{
			assert_error("Unclosed quote");
		}
		add_character(new_word, *current_word);
		current_word++;
	}
	*rest = current_word;
}

static void	remove_double_quote(char **new_word, char **rest,
		char *current_word)
{
	char	quote;

	quote = *current_word;
	current_word++;
	while (*current_word != quote)
	{
		if (*current_word == '\0')
			fatal_error("Unclosed quote");
		else if (is_variable(current_word))
		{
			append_variable(new_word, &current_word, current_word);
		}
		else if (is_special_parameter(current_word))
			append_special_param(new_word, &current_word, current_word);
		else
		{
			add_character(new_word, *current_word);
			current_word++;
		}
	}
	*rest = current_word;
}

static void	exception_only_quote_word(char **new_word)
{
	*new_word = ft_strdup("");
	if (*new_word == NULL)
	{
		fatal_error("ft_strdup");
	}
}

static void	do_remove_quote(char **new_word, char *current_word)
{
	if (ft_strcmp(current_word, "\"\"") == 0
		|| ft_strcmp(current_word, "''") == 0)
	{
		return (exception_only_quote_word(new_word));
	}
	while (*current_word != '\0')
	{
		if (*current_word == SINGLE_QUOTE_CHAR)
			remove_quote(new_word, &current_word, current_word);
		else if (*current_word == DOUBLE_QUOTE_CHAR)
			remove_double_quote(new_word, &current_word, current_word);
		else if (is_variable(current_word))
		{
			append_variable(new_word, &current_word, current_word);
			continue ;
		}
		else if (is_special_parameter(current_word))
		{
			append_special_param(new_word, &current_word, current_word);
			continue ;
		}
		else
			add_character(new_word, *current_word);
		current_word++;
	}
}

void	try_remove_quote(t_token *token)
{
	char	*new_word;

	new_word = NULL;
	while (token != NULL)
	{
		if (token->kind != TK_WORD)
		{
			token = token->next;
			continue ;
		}
		if (token->word == NULL)
			fatal_error("try_remove_quote");
		do_remove_quote(&new_word, token->word);
		free(token->word);
		token->word = new_word;
		new_word = NULL;
		token = token->next;
	}
}
