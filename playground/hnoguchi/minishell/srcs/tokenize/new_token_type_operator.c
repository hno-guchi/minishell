/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_type_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/22 12:27:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_operator(char *str, const char *operator)
{
	return (ft_memcmp(str, operator, ft_strlen(operator)) == 0);
}

static bool	is_control(char *operator)
{
	char *const	control_list[] = {"|"};
	int			i;

	i = 0;
	while (i < SIZE_CONTROL_LIST)
	{
		if (is_operator(operator, control_list[i]))
		{
			return (true);
		}
		i += 1;
	}
	return (false);
}

static bool	is_redirection(char *operator)
{
	char *const	redirection_list[] = {">>", "<<", ">", "<"};
	int			i;

	i = 0;
	while (i < SIZE_REDIRECTION_LIST)
	{
		if (is_operator(operator, redirection_list[i]))
		{
			return (true);
		}
		i += 1;
	}
	return (false);
}

static t_token	*try_new_token(const char *operator)
{
	char	*dup;

	dup = ft_strdup(operator);
	if (dup == NULL)
	{
		fatal_error("ft_strdup");
	}
	else if (is_control(dup))
	{
		return (new_token(TK_CONTROL, dup));
	}
	else if (is_redirection(dup))
	{
		return (new_token(TK_REDIRECTION, dup));
	}
	free(dup);
	return (NULL);
}

t_token	*new_token_type_operator(char **rest, char *line)
{
	char *const	operator_list[] = {">>", "<<", ">", "<", "|"};
	t_token		*new;
	int			i;

	i = 0;
	while (i < SIZE_OPERATOR_LIST)
	{
		if (is_operator(line, operator_list[i]))
		{
			new = try_new_token(operator_list[i]);
			if (new == NULL)
			{
				fatal_error("try_new_token");
			}
			*rest = line + ft_strlen(operator_list[i]);
			return (new);
		}
		i += 1;
	}
	tokenize_error(*line, &line, line);
	return (NULL);
}
