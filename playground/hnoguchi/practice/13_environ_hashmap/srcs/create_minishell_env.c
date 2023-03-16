/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minishell_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 11:55:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static size_t	count_item(void)
{
	size_t	count;
	t_item	*item;

	count = 0;
	item = g_env->head_p;
	while (item->next != NULL)
	{
		count += 1;
		item = item->next;
	}
	return (count);
}

static size_t	item_strlen(t_item *item)
{
	size_t	len;

	len = 0;
	if (item->name != NULL)
	{
		len = ft_strlen(item->name);
	}
	if (item->value != NULL)
	{
		len += ft_strlen(item->value);
	}
	return (len);
}

static char	*cat_name_equol_value(t_item *item)
{
	char	*env;
	size_t	str_size;

	env = NULL;
	str_size = item_strlen(item);
	if (str_size == 0)
	{
		return (NULL);
	}
	env = ft_calloc(str_size + 2, sizeof(char));
	if (env == NULL)
	{
		fatal_error("ft_calloc");
	}
	if (item->name != NULL)
	{
		ft_strlcpy(env, item->name, str_size + 2);
	}
	ft_strlcat(env, "=", str_size + 2);
	if (item->value != NULL)
	{
		ft_strlcat(env, item->value, str_size + 2);
	}
	return (env);
}

char	**create_minishell_env(void)
{
	char	**head_p;
	char	**minishell_env;
	t_item	*item;
	size_t	env_size;

	item = g_env->head_p->next;
	env_size = count_item();
	minishell_env = ft_calloc(env_size + 1, sizeof(char *));
	head_p = minishell_env;
	if (minishell_env == NULL)
	{
		fatal_error("ft_calloc");
	}
	while (item != NULL)
	{
		*minishell_env = cat_name_equol_value(item);
		if (*minishell_env != NULL)
		{
			minishell_env += 1;
		}
		item = item->next;
	}
	return (head_p);
}
