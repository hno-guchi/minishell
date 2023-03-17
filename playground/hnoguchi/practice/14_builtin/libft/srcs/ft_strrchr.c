/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:00:01 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:12:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				i;
	size_t				max;
	unsigned char		chr;
	const char			*p;

	i = 0;
	max = ft_strlen(s);
	chr = (unsigned char)c;
	p = 0;
	if (chr == '\0')
		return ((char *)&s[max]);
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			p = &s[i];
		i += 1;
	}
	return ((char *)p);
}
