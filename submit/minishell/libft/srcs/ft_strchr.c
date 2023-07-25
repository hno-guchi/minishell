/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:55:14 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:11:38 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			max;
	unsigned char	chr;

	i = 0;
	max = ft_strlen(s);
	chr = (unsigned char)c;
	if (chr == '\0')
		return ((char *)&s[max]);
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
		i += 1;
	}
	return (NULL);
}
