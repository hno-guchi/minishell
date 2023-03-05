/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:02:36 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 15:40:14 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

bool	is_special_parameter(const char *str)
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

void	append_num(char **new_word, unsigned int num)
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

void	append_special_param(char **new_word, int status, char **rest, char *current_word)
{
	if (current_word == NULL)
	{
		return ;
	}
	current_word += 2;
	append_num(new_word, status);
	*rest = current_word;
}

/*
# define TEST_CASE 10
int	main(void)
{
	int					i;
	char				*result;
	unsigned int		test_case[] = {
		0,
		10,
		100,
		1000,
		258,
		904,
		49008,
		555,
		34083,
		20114,
	};

	i = 0;
	result = NULL;
	while(i < TEST_CASE)
	{
		append_num(&result, test_case[i]);
		dprintf(STDOUT_FILENO, "[%5d] -> [%5s]\n", test_case[i], result);
		free(result);
		result = NULL;
		i += 1;
	}

}
*/
