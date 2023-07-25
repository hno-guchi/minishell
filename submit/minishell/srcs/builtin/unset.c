/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:30:19 by asasada           #+#    #+#             */
/*   Updated: 2023/03/26 20:43:32 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_node *node)
{
	t_token	*args;
	int		ret;

	ret = 0;
	args = node->command->args->next;
	while (args != NULL)
	{
		if (args->word == NULL)
		{
			args = args->next;
			continue ;
		}
		if (is_valid_env_var_name(args->word))
		{
			unset_map(args->word);
		}
		else
		{
			builtin_error("unset", args->word, "not a valid identifier");
			ret = 1;
		}
		args = args->next;
	}
	return (ret);
}
