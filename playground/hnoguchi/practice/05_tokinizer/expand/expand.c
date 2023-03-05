/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:06:02 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 11:12:28 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static void	add_character(char **word, char c)
{
	size_t	size;
	char	*temp;

	size = 2;
	if (*word != NULL)
	{
		size += strlen(*word);
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			fatal_error("malloc");
		}
		strlcpy(temp, *word, size);
		free(*word);
	}
	else
	{
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			fatal_error("malloc");
		}
	}
	temp[size - 2] = c;
	temp[size - 1] = '\0';
	*word = temp;
}

static void	remove_quote(char **new_word, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
	// while (*current_word != '\0')
	// {
		current_word++;
		while (*current_word != quote)
		{
			if (*current_word == '\0')
			{
				fatal_error("Unclosed quote");
			}
			add_character(new_word, *current_word);
			current_word++;
		}
	// }
	*rest = current_word;
}

static void	try_remove_quote(t_token *token)
{
	char	*new_word;
	char	*current_word;

	new_word = NULL;
	current_word = token->word;
	while (*current_word != '\0')
	{
		if (*current_word == SINGLE_QUOTE_CHAR)
		{
			remove_quote(&new_word, &current_word, current_word);
		}
		else if (*current_word == DOUBLE_QUOTE_CHAR)
		{
			// current_word++;
			remove_quote(&new_word, &current_word, current_word);
		}
		else
		{
			add_character(&new_word, *current_word);
		}
		current_word++;
	}
	free(token->word);
	token->word = new_word;
}

t_token	*expand(t_token *token)
{
	t_token	*head_p;

	head_p = token;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			// printf("Before == [%s];\n", token->word);
			try_remove_quote(token);
			// printf("Atere  == [%s];\n", token->word);
		}
		token = token->next;
	}
	return (head_p);
}
