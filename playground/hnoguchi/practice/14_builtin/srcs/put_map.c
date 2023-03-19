/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/19 19:47:28 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	put_only_name(char **name, const char *string, char *equol_p)
{
	if (equol_p == NULL)
	{
		*name = ft_strdup(string);
		if (*name == NULL)
		{
			fatal_error("ft_strdup");
		}
	}
	else if (*(equol_p + 1) == '\0')
	{
		*name = ft_strndup(string, equol_p - string);
		if (*name == NULL)
		{
			fatal_error("ft_strndup");
		}
	}
}

static void	put_name_and_value(char **name, char **value,
		const char *string, char *equol_p)
{
	*name = ft_strndup(string, equol_p - string);
	if (*name == NULL)
	{
		fatal_error("ft_strndup");
	}
	*value = ft_strdup(equol_p + 1);
	if (*value == NULL)
	{
		fatal_error("ft_strdup");
	}
}

int	put_map(const char *string)
{
	char	*name;
	char	*value;
	char	*name_tail_p;

	name = NULL;
	value = NULL;
	if (string == NULL)
	{
		return (1);
	}
	name_tail_p = ft_strchr(string, '=');
	if (name_tail_p == NULL || *(name_tail_p + 1) == '\0')
	{
		put_only_name(&name, string, name_tail_p);
	}
	else
	{
		put_name_and_value(&name, &value, string, name_tail_p);
	}
	set_map(name, value);
	free(name);
	free(value);
	return (0);
}
