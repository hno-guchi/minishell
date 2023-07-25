/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/26 12:06:39 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_only_name(char **name, const char *string, char *equal_p)
{
	if (equal_p == NULL)
	{
		*name = ft_strdup(string);
		if (*name == NULL)
		{
			fatal_error("ft_strdup");
		}
	}
	else if (*(equal_p + 1) == '\0')
	{
		*name = ft_strndup(string, equal_p - string);
		if (*name == NULL)
		{
			fatal_error("ft_strndup");
		}
	}
}

static void	put_name_and_value(char **name, char **value,
		const char *string, char *equal_p)
{
	*name = ft_strndup(string, equal_p - string);
	if (*name == NULL)
	{
		fatal_error("ft_strndup");
	}
	if (equal_p[1] == '\0')
		*value = ft_strdup("");
	else
		*value = ft_strdup(equal_p + 1);
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
	if (name_tail_p == NULL)
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
