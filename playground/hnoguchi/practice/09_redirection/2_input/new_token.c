/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/10 14:35:00 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token	*new_token(t_token_kind kind, char *word)
{
	t_token	*new_token;

	new_token = calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		fatal_error("calloc");
	}
	new_token->word = word;
	new_token->kind = kind;
	new_token->file_fd = 0;
	new_token->next = NULL;
	return (new_token);
}

t_token	*new_token_type_operator(char **rest, char *line)
{
	static char *const	operators_list[] = {"||", "&&", ";;", ">", "<", "|", "&", ";", "(", ")", "\n"};
	char				*operator;
	int					i;

	operator = NULL;
	i = 0;
	while (i < SIZE_OPERATORS_LIST)
	{
		if (is_operator(line, operators_list[i]))
		{
			operator = strdup(operators_list[i]);
			if (operator == NULL)
			{
				fatal_error("strdup");
			}
			else
			{
				*rest = line + strlen(operator);
				return (new_token(TK_OPERATOR, operator));
			}
		}
		i += 1;
	}
	fatal_error("Not operator...");
	return (NULL);
}

t_token	*new_token_type_word(char **rest, char *line)
{
	const char	*start_p;
	char		*word;

	start_p = line;
	word = NULL;
	while (*line)
	{
		if (is_meta_character(*line))
		{
			break ;
		}
		else if (is_blank(*line))
		{
			break ;
		}
		else if (*line == SINGLE_QUOTE_CHAR)
		{
			line++;
			while (*line != SINGLE_QUOTE_CHAR)
			{
				if (*line == '\0')
				{
					fatal_error("Unclosed single quote");
				}
				line++;
			}
			line++;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			line++;
			while (*line != DOUBLE_QUOTE_CHAR)
			{
				if (*line == '\0')
				{
					fatal_error("Unclosed double quote");
				}
				line++;
			}
			line++;
		}
		else
		{
			line++;
		}
	}
	word = strndup(start_p, line - start_p);
	if (word == NULL)
	{
			fatal_error("strndup");
	}
	else
	{
		*rest = line;
		return (new_token(TK_WORD, word));
	}
	fatal_error("Not word...");
	return (NULL);
}
