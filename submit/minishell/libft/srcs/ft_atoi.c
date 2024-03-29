/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:14:12 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/24 20:08:10 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	change_format(const char *str, int sign);

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (ft_isspace(str[i]) == 1)
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i += 1;
	}
	num = change_format(&str[i], sign);
	return (num);
}

static int	change_format(const char *str, int sign)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		if (num <= ((LONG_MAX - (str[i] - '0')) / 10))
			num = (num * 10) + (str[i] - '0');
		else
		{
			if (sign == -1)
				return ((int)LONG_MIN);
			else
				return ((int)LONG_MAX);
		}
		i += 1;
	}
	num *= (long long )sign;
	return ((int)num);
}
