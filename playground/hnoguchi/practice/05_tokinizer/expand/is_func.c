/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 10:46:32 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		*rest = line + 1;
		return (true);
	}
	*rest = line;
	return (false);
}

bool	is_meta_character(const char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

bool	is_operator(char *str, const char *operator)
{
	return (memcmp(str, operator, strlen(operator)) == 0);
}

bool	is_word(char c)
{
	if (is_blank(c))
	{
		return (false);
	}
	if (is_meta_character(c))
	{
		return (false);
	}
	return (true);
}
