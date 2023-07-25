/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:41:18 by asasada           #+#    #+#             */
/*   Updated: 2023/03/24 20:24:51 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(const char *word)
{
	if (word == NULL)
	{
		return (false);
	}
	if (*word != '-')
	{
		return (false);
	}
	word += 1;
	while (*word != '\0')
	{
		if (*word != 'n')
		{
			return (false);
		}
		word += 1;
	}
	return (true);
}

static bool	consume_n_option(t_token **rest, t_token *args)
{
	bool	n_flag;

	n_flag = false;
	while (args != NULL)
	{
		if (!is_option(args->word))
		{
			break ;
		}
		n_flag = true;
		args = args->next;
	}
	*rest = args;
	return (n_flag);
}

int	builtin_echo(t_node *node)
{
	bool	n_flag;
	t_token	*args;

	n_flag = false;
	args = node->command->args->next;
	n_flag = consume_n_option(&args, args);
	while (args != NULL)
	{
		if (args->word == NULL)
		{
			args = args->next;
			continue ;
		}
		ft_putstr_fd(args->word, STDOUT_FILENO);
		if (args->next != NULL && args->next->word != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		args = args->next;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
