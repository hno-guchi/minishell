/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 19:45:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	item = g_minishell.env->head_p;
	if (name == NULL)
		return (NULL);
	while (item->next != NULL)
	{
		if (ft_strcmp(item->next->name, name) == 0)
		{
			if (item->next->value == NULL)
			{
				return (NULL);
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

int	unset_map(const char *name)
{
	t_item	*prev_item;
	t_item	*target_item;

	if (name == NULL)
	{
		return (1);
	}
	prev_item = g_minishell.env->head_p;
	target_item = g_minishell.env->head_p->next;
	while (target_item != NULL)
	{
		if (ft_strcmp(target_item->name, name) == 0)
		{
			prev_item->next = target_item->next;
			frees_item(target_item);
			return (0);
		}
		prev_item = target_item;
		target_item = target_item->next;
	}
	return (1);
}
