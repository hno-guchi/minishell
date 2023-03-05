/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:02:33 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 14:54:56 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variable.h"

/*
 * man bash
 *
 * PARAMETERS
 * A parameter is an entity that stores values.
 * It can be a name, a number, or one of the special characters listed below under Special Parameters.
 * A variable is a parameter denoted by a name.
 * A variable has a value and zero or more attributes.
 * Attributes are assigned using the declare builtin command (see declare below in SHELL BUILTIN COMMANDS).
 *
 * DEFINITIONS
 * The following definitions are used throughout the rest of this document.
 * blank  A space or tab.
 * word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
 * name   A word consisting only of alphanumeric characters and underscores,
 *        and beginning with an alphabetic character or an underscore.
 *        Also referred to as an identifier.
 */


// Beginning with an alphabetic character or an underscore.
bool	is_alpha_underscore(const char c)
{
	return (isalpha(c) || c == '_');
}

// A word consisting only of alphanumeric characters and underscores.
bool	is_alnum_underscore(const char c)
{
	return (isalnum(c) || c == '_');
}

bool	is_identifier(const char *str)
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

bool	is_variable(const char *str)
{
	return (str[0] == '$' && is_alpha_underscore(str[1]));
}

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

void	add_character(char **word, char c)
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

void	append_variable_str(char **new_word, char **rest, char *current_word)
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
		// fatal_error("getenv");
	}
	free(variable_name);
	while (*value != '\0')
	{
		add_character(new_word, *value);
		value++;
	}
	// Error!!
	// free(head_p);
}

void	append_variable(char **new_word, char **rest, char *current_word)
{
	// char	quote;

	// quote = *current_word;
	// current_word++;
	// while (*current_word != quote)
	if (current_word == NULL)
	{
		return ;
	}
	while (*current_word != '\0')
	{
		// if (*current_word == '\0')
		// {
		// 	fatal_error("Unclosed quote");
		// }
		if (is_variable(current_word))
		{
			append_variable_str(new_word, &current_word, current_word);
			continue ;
		}
		add_character(new_word, *current_word);
		current_word++;
	}
	*rest = current_word;
}

/*
int	main(void)
{
	char	*test_case[] = {
		"$USER",
		"hello$USER",
		"hello $USER",
		"$USERhello",
		"hello$USERworld",
		"$USER$SHELL",
		"$USER $SHELL",
		NULL,
	};
	char	*result;
	size_t	i;

	i = 0;
	result = NULL;
	while (test_case[i] != NULL)
	{
		dprintf(STDOUT_FILENO, "===============\n");
		dprintf(STDOUT_FILENO, "test_case[%02zu] : [%s]\n", i, test_case[i]);
		append_variable(&result, &test_case[i], test_case[i]);
		dprintf(STDOUT_FILENO, "-> result     : [%s]\n", result);
		free(result);
		result = NULL;
		i += 1;
	}
	system("leaks -q only_getenv");
}
*/
