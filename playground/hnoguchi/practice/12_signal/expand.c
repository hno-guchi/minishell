/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:06:02 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 19:04:18 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alpha_underscore(const char c)
{
	return (isalpha(c) || c == '_');
}

static bool	is_alnum_underscore(const char c)
{
	return (isalnum(c) || c == '_');
}

/*
static bool	is_identifier(const char *str)
{
	if (!is_alpha_underscore(*str))
	{
		return (false);
	}
	str++;
	while (*str != '\0')
	{
		if (!is_alnum_underscore(*str))
		{
			return (false);
		}
		str++;
	}
	return (true);
}
*/

static bool	is_variable(const char *str)
{
	return (str[0] == '$' && is_alpha_underscore(str[1]));
}

static bool	is_special_parameter(const char *str)
{
	return (str[0] == '$' && str[1] == '?');
}

static void	add_character(char **word, char c)
{
	size_t	size;
	char	*temp;

	size = 2;
	temp = NULL;
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

static void	append_variable_str(char **new_word, char **rest, char *current_word)
{
	char	*value;
	char	*variable_name;

	value = NULL;
	variable_name = NULL;
	current_word++;
	while (is_alnum_underscore(*current_word))
	{
		add_character(&variable_name, *current_word);
		current_word++;
		if (*current_word == '\0')
		{
			break ;
		}
	}
	*rest = current_word;
	value = getenv(variable_name);
	if (value == NULL)
	{
		free(variable_name);
		return ;
	}
	free(variable_name);
	while (*value != '\0')
	{
		add_character(new_word, *value);
		value++;
	}
}

static void	append_num(char **new_word, unsigned int num)
{
	if (num == 0)
	{
		add_character(new_word, '0');
		return ;
	}
	if ((num / 10) != 0)
	{
		append_num(new_word, num / 10);
	}
	add_character(new_word, '0' + (num % 10));
}

static void	append_special_param(char **new_word, int status, char **rest, char *current_word)
{
	if (current_word == NULL)
	{
		return ;
	}
	current_word += 2;
	// dprintf(STDOUT_FILENO, "current_word [%s]\n", current_word);
	append_num(new_word, (unsigned int)status);
	*rest = current_word;
}

static void	remove_quote(char **new_word, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
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
	*rest = current_word;
}

static void	remove_double_quote(char **new_word, int last_status, char **rest, char *current_word)
{
	char	quote;

	quote = *current_word;
	current_word++;
	while (*current_word != quote)
	{
		if (*current_word == '\0')
		{
			fatal_error("remove_double_quote : Unclosed quote");
		}
		else if (is_variable(current_word))
		{
			append_variable_str(new_word, &current_word, current_word);
			// continue ;
		}
		else if (is_special_parameter(current_word))
		{
			// dprintf(STDOUT_FILENO, "current_word [%s]\n", current_word);
			append_special_param(new_word, last_status, &current_word, current_word);
		}
		else
		{
			add_character(new_word, *current_word);
			current_word++;
		}
	}
	*rest = current_word;
}

static void	try_remove_quote(t_token *token)
{
	char	*new_word;
	char	*current_word;

	new_word = NULL;
	current_word = NULL;
	// while (token->kind != TK_EOF)
	while (token != NULL)
	{
		if (token->kind != TK_WORD)
		{
			token = token->next;
			continue ;
		}
		current_word = token->word;
		// printf("Before == [%s];\n", token->word);
		while (*current_word != '\0')
		{
			if (*current_word == SINGLE_QUOTE_CHAR)
			{
				remove_quote(&new_word, &current_word, current_word);
			}
			else if (*current_word == DOUBLE_QUOTE_CHAR)
			{
				remove_double_quote(&new_word, token->last_status, &current_word, current_word);
			}
			else if (is_variable(current_word))
			{
				append_variable_str(&new_word, &current_word, current_word);
				// continue ;
			}
			else if (is_special_parameter(current_word))
			{
				append_special_param(&new_word, token->last_status, &current_word, current_word);
			}
			else
			{
				add_character(&new_word, *current_word);
			}
			current_word++;
		}
		free(token->word);
		current_word = NULL;
		token->word = new_word;
		new_word = NULL;
		// printf("Atere  == [%s];\n", token->word);
		token = token->next;
	}
}

static void	expand_redirects(t_node *redir)
{
	if (redir == NULL)
	{
		return ;
	}
	while (redir != NULL)
	{
		try_remove_quote(redir->args);
		redir = redir->next;
	}
}

t_node	*expand(t_node *node)
{
	t_node	*head_p;

	if (node == NULL)
	{
		return (NULL);
	}
	head_p = node;
	while (node != NULL)
	{
		try_remove_quote(node->command->args);
		expand_redirects(node->command->redirects);
		node = node->next;
	}
	return (head_p);
}
