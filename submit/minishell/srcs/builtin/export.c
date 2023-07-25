/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:00:12 by asasada           #+#    #+#             */
/*   Updated: 2023/03/20 22:00:12 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_env_var_name(const char *str)
{
	if (!is_alpha_underscore(*str))
	{
		return (false);
	}
	str++;
	while (*str != '\0')
	{
		if (!is_alnum_underscore(*str))
		{
			return (false);
		}
		str++;
	}
	return (true);
}

static void	export_print_map(void)
{
	t_item	*item;

	item = g_minishell.env->head_p->next;
	while (item != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(item->name, STDOUT_FILENO);
		if (item->value != NULL)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(item->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		item = item->next;
	}
}

static char	*get_key_name(char *str)
{
	char	*key_tail_p;
	char	*key;

	key_tail_p = ft_strchr(str, '=');
	if (key_tail_p == NULL)
		key = ft_strdup(str);
	else
		key = ft_strndup(str, key_tail_p - str);
	if (key == NULL)
		fatal_error("ft_strdup() or ft_strndup()");
	return (key);
}

int	builtin_export(t_node *node)
{
	t_token	*arg;
	char	*key;
	int		status;

	arg = node->command->args->next;
	if (arg == NULL)
	{
		export_print_map();
		return (0);
	}
	while (arg != NULL)
	{
		key = get_key_name(arg->word);
		if (!is_valid_env_var_name(key))
		{
			builtin_error("export", key, "not a valid identifier");
			status = 1;
		}
		else
			put_map(arg->word);
		free(key);
		arg = arg->next;
	}
	return (status);
}
