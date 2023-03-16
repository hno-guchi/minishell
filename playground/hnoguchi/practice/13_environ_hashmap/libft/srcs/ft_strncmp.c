/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:01:12 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:13:06 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	if (n == 0)
		return (0);
	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < (n - 1))
	{
		if (s1_uc[i] == '\0' || s2_uc[i] == '\0')
			return (s1_uc[i] - s2_uc[i]);
		if ((s1_uc[i] - s2_uc[i]) != 0)
			return (s1_uc[i] - s2_uc[i]);
		i += 1;
	}
	return (s1_uc[i] - s2_uc[i]);
}
