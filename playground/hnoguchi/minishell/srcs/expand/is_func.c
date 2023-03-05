/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:55 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:01:03 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alpha_underscore(const char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alnum_underscore(const char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_variable(const char *str)
{
	return (str[0] == '$' && is_alpha_underscore(str[1]));
}

bool	is_special_parameter(const char *str)
{
	return (str[0] == '$' && str[1] == '?');
}

/*
static bool	is_identifier(const char *str)
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
*/
