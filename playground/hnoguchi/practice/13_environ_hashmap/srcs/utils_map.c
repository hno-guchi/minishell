/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 16:13:05 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

t_environ	*new_map(void)
{
	t_environ	*new;

	new = calloc(1, sizeof(t_environ));
	if (new == NULL)
	{
		fatal_error("calloc");
	}
	new->head_p = ft_calloc(1, sizeof(t_item));
	if (new->head_p == NULL)
	{
		fatal_error("calloc");
	}
	return (new);
}

t_item	*new_item(char *name, char *value)
{
	t_item	*new;

	new = NULL;
	if (name == NULL)
	{
		return (NULL);
	}
	new = ft_calloc(1, sizeof(t_item));
	if (new == NULL)
	{
		fatal_error("calloc");
	}
	new->name = ft_strdup(name);
	if (new->name == NULL)
	{
		fatal_error("strdup");
	}
	if (value != NULL)
	{
		new->value = ft_strdup(value);
		if (new->value == NULL)
			fatal_error("strdup");
	}
	return (new);
}

char	*get_map_value(const char *name)
{
	char	*dup_value;
	t_item	*item;

	dup_value = NULL;
	item = g_env->head_p;
	if (name == NULL)
		return (NULL);
	while (item->next != NULL)
	{
		if (ft_strcmp(item->next->name, name) == 0)
		{
			if (item->next->value == NULL)
			{
				break ;
			}
			dup_value = ft_strdup(item->next->value);
			if (dup_value == NULL)
			{
				fatal_error("strdup");
			}
			return (dup_value);
		}
		item = item->next;
	}
	return (NULL);
}
