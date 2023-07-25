/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/26 22:47:26 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_set_value(t_item *item, const char *value, bool null_overwrite)
{
	char	*dup_value;

	if (value == NULL && !null_overwrite)
	{
		return (0);
	}
	if (value != NULL)
	{
		dup_value = ft_strdup(value);
		if (dup_value == NULL)
		{
			fatal_error("ft_strdup");
		}
	}
	else
	{
		dup_value = (char *)value;
	}
	if (item->value != NULL)
	{
		free(item->value);
	}
	item->value = dup_value;
	return (0);
}

static int	try_set_existing_name(const char *name, const char *value,
		bool null_overwrite)
{
	t_item	*item;

	item = g_minishell.env->head_p->next;
	while (item != NULL)
	{
		if (ft_strcmp(item->name, name) == 0)
		{
			return (try_set_value(item, value, null_overwrite));
		}
		item = item->next;
	}
	return (1);
}

static int	try_set_new_item(char *name, char *value)
{
	t_item	*new;
	t_item	*item;

	item = NULL;
	new = new_item(name, value);
	if (new == NULL)
	{
		return (1);
	}
	item = g_minishell.env->head_p;
	while (item->next != NULL)
	{
		item = item->next;
	}
	item->next = new;
	return (0);
}

int	set_map(const char *name, const char *value)
{
	if (name == NULL)
	{
		return (1);
	}
	if (try_set_existing_name(name, value, false) == 0)
	{
		return (0);
	}
	if (try_set_new_item((char *)name, (char *)value) == 0)
	{
		return (0);
	}
	return (1);
}

int	set_map_overwrite(const char *name, const char *value)
{
	if (name == NULL)
	{
		return (1);
	}
	if (try_set_existing_name(name, value, true) == 0)
	{
		return (0);
	}
	if (try_set_new_item((char *)name, (char *)value) == 0)
	{
		return (0);
	}
	return (1);
}
