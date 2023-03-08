/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 17:10:54 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_meta_character(const char c)
{
	if (is_blank(c))
	{
		return (true);
	}
	return (c && ft_strchr("|&;()<>\n", c));
}

static bool	consume_blank(char **rest, char *line)
{
	if (*line != '\0' && is_blank(*line))
	{
		*rest = line + 1;
		return (true);
	}
	*rest = line;
	return (false);
}

static bool	is_word(char c)
{
	if (is_meta_character(c))
	{
		return (false);
	}
	return (true);
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*current_token;

	head.next = NULL;
	current_token = &head;
	g_minishell.syntax_error = false;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_meta_character(*line))
		{
			current_token->next = new_token_type_operator(&line, line);
			current_token = current_token->next;
		}
		else if (is_word(*line))
		{
			current_token->next = new_token_type_word(&line, line);
			current_token = current_token->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	current_token->next = new_token(TK_EOF, NULL);
	return (head.next);
}
