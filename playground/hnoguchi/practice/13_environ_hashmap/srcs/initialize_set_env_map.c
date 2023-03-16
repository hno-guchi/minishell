/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_set_env_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 11:55:37 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	set_item(t_item *item, char *env)
{
	char		*name;
	char		*value;
	char		*env_equol_p;
	size_t		env_len;

	name = NULL;
	value = NULL;
	env_len = ft_strlen(env);
	env_equol_p = ft_strchr(env, '=');
	if (env_equol_p == NULL)
		return (0);
	name = ft_strndup(env, (env_equol_p - env));
	if (name == NULL)
		return (0);
	value = ft_strndup(env_equol_p + 1, env_len - (env_equol_p - env));
	if (value == NULL)
		return (0);
	item->next = new_item(name, value);
	free(name);
	free(value);
	return (1);
}

void	initialize_set_env_map(void)
{
	t_item		*item;
	extern char	**environ;
	char		**env;

	env = environ;
	g_env = new_map();
	item = g_env->head_p;
	while (*env != NULL)
	{
		if (set_item(item, *env) == 0)
		{
			frees_map();
			fatal_error("set_item");
		}
		item = item->next;
		env += 1;
	}
}
