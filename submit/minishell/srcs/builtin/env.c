/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:07:09 by asasada           #+#    #+#             */
/*   Updated: 2023/03/19 22:07:09 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(void)
{
	t_item	*item;

	item = g_minishell.env->head_p->next;
	while (item != NULL)
	{
		if (item->value != NULL)
		{
			ft_putstr_fd(item->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(item->value, STDOUT_FILENO);
		}
		item = item->next;
	}
	return (0);
}
