/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:01:12 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/01 15:34:57 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (*s1_uc != '\0' && *s2_uc != '\0')
	{
		if ((*s1_uc - *s2_uc) != 0)
		{
			return (*s1_uc - *s2_uc);
		}
		s1_uc++;
		s2_uc++;
	}
	return (*s1_uc - *s2_uc);
}
