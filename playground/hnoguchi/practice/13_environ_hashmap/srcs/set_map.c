/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 19:39:43 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static char	*try_set_value(const char *value)
{
	char	*dup_value;

	dup_value = NULL;
	if (value != NULL)
	{
		dup_value = ft_strdup(value);
		if (dup_value == NULL)
		{
			fatal_error("ft_strdup");
		}
		return (dup_value);
	}
	return (NULL);
}

static int	try_set_existing_name(const char *name, const char *value)
{
	t_item	*item;

	item = g_env->head_p->next;
	while (item != NULL)
	{
		if (ft_strcmp(item->name, name) == 0)
		{
			if (item->value != NULL)
			{
				free(item->value);
			}
			item->value = try_set_value(value);
			return (0);
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
	item = g_env->head_p;
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
	if (try_set_existing_name(name, value) == 0)
	{
		return (0);
	}
	if (try_set_new_item((char *)name, (char *)value) == 0)
	{
		return (0);
	}
	return (0);
}
