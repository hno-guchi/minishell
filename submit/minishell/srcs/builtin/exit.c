/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:01:46 by asasada           #+#    #+#             */
/*   Updated: 2023/03/26 21:01:46 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(char *str)
{
	int	i;

	if (str == NULL)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(t_node *node)
{
	t_token	*args;
	long	ret;
	char	*endptr;

	args = node->command->args;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (arglen(args) == 1)
		exit((int)g_minishell.last_status);
	else if (arglen(args) >= 3 && is_numeric(args->next->word))
	{
		builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	else if (is_numeric(args->next->word))
	{
		errno = 0;
		ret = strtol_base_10(args->next->word, &endptr);
		if (errno == 0 && *endptr == '\0')
			exit((int)ret);
	}
	builtin_error("exit", args->next->word, "numeric argument required");
	exit(255);
	return (0);
}
