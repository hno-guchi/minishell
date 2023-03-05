/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:55 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/01/31 16:36:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "fatal_error: %s", message);
	exit(1);
}

static void	add_character(char **new_word, char c)
{
	size_t	size;
	char	*temp;

	size = 2;
	if (*new_word != NULL)
	{
		size += strlen(*new_word);
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			fatal_error("malloc");
		}
		strlcpy(temp, *new_word, size);
		free(*new_word);
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
	*new_word = temp;
}

static char	*remove_quote(char *word)
{
	char	*current_word;
	char	*new_word;

	current_word = word;
	new_word = NULL;
	while (*current_word != '\0')
	{
		if (*current_word == SINGLE_QUOTE_CHAR)
		{
			current_word++;
			while (*current_word != SINGLE_QUOTE_CHAR)
			{
				if (*current_word == '\0')
				{
					fatal_error("Unclosed quote.");
				}
				add_character(&new_word, *current_word);
				current_word++;
			}
			current_word++;
		}
		else if (*current_word == DOUBLE_QUOTE_CHAR)
		{
			current_word++;
			while (*current_word != DOUBLE_QUOTE_CHAR)
			{
				if (*current_word == '\0')
				{
					dprintf(STDERR_FILENO, "Un closed quote.");
					exit(1);
				}
				add_character(&new_word, *current_word);
				current_word++;
			}
			current_word++;
		}
		else
		{
			add_character(&new_word, *current_word);
			current_word++;
		}
	}
	return (new_word);
}

// "\"Hello!\""
// "'Good morning.'"
// "'Hello'\"42Tokyo,'Bonjour'\""
int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Not argv.");
		exit (1);
	}
	printf("Before : [%s]\n", argv[1]);
	printf("After  : [%s]\n", remove_quote(argv[1]));
	exit (0);
}
