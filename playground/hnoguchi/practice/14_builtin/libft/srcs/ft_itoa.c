/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:39:29 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:50:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long long int ln);
static size_t	check_negative(long long int ln);

char	*ft_itoa(int n)
{
	long long int	l_num;
	size_t			negative;
	size_t			digits;
	char			*str;

	l_num = (long long int)n;
	negative = check_negative(l_num);
	digits = count_digits(l_num);
	str = (char *)ft_calloc(negative + digits + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (negative == 1)
	{
		str[0] = '-';
		l_num *= -1;
	}
	str[negative + digits] = '\0';
	while (0 < digits)
	{
		digits -= 1;
		str[negative + digits] = (l_num % 10) + '0';
		l_num /= 10;
	}
	return (str);
}

static size_t	count_digits(long long int ln)
{
	size_t	digits;

	digits = 1;
	if (ln < 0)
		ln *= -1;
	while (9 < ln)
	{
		digits += 1;
		ln = ln / 10;
	}
	return (digits);
}

static size_t	check_negative(long long int ln)
{
	if (ln < 0)
		return (1);
	else
		return (0);
}
