/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 12:03:39 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	frees_item(t_item *item)
{
	if (item->name != NULL)
	{
		free(item->name);
	}
	if (item->value != NULL)
	{
		free(item->value);
	}
	free(item);
}

void	frees_map(void)
{
	t_item	*item;
	t_item	*next_item;

	item = g_env->head_p;
	while (item != NULL)
	{
		next_item = item->next;
		frees_item(item);
		item = next_item;
	}
}

void	frees_env(char **env)
{
	char	**head_p;

	head_p = env;
	while (*env != NULL)
	{
		free(*env);
		env += 1;
	}
	free(head_p);
}
