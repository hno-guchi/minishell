/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:57 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:36:42 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	join_size(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	dstsize;
	char	*dst;

	dstsize = 0;
	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	dstsize = join_size(s1, s2);
	dst = (char *)ft_calloc(dstsize, sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		(void)ft_strlcpy(dst, s2, dstsize);
	else if (s1 != NULL && s2 == NULL)
		(void)ft_strlcpy(dst, s1, dstsize);
	else
	{
		(void)ft_strlcpy(dst, s1, dstsize);
		(void)ft_strlcat(dst, s2, dstsize);
	}
	return (dst);
}

static size_t	join_size(char const *s1, char const *s2)
{
	size_t	dstsize;
	size_t	s2_siz;

	dstsize = 0;
	s2_siz = 0;
	if (s1 != NULL)
		dstsize = ft_strlen(s1);
	if (s2 != NULL)
		s2_siz = ft_strlen(s2);
	if (s2_siz < (SIZE_MAX - dstsize))
		dstsize += s2_siz + 1;
	else
		dstsize = SIZE_MAX;
	return (dstsize);
}
