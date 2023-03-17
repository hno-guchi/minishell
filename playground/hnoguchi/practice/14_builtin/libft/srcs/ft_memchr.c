/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:06:36 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:13:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*s_uc;

	i = 0;
	uc = (unsigned char)c;
	s_uc = (unsigned char *)s;
	while (i < n)
	{
		if (s_uc[i] == uc)
			return (&s_uc[i]);
		i += 1;
	}
	return (NULL);
}
