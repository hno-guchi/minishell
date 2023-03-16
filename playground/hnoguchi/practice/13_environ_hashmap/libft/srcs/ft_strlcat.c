/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:34:30 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:09:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t n);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;
	size_t	lcat_siz;

	i = 0;
	d_len = ft_strnlen(dst, dstsize);
	s_len = ft_strlen(src);
	if (dstsize <= d_len)
		return (dstsize + s_len);
	if (s_len < (dstsize - d_len - 1))
		lcat_siz = s_len + 1;
	else
		lcat_siz = dstsize - d_len - 1;
	while (i < lcat_siz)
	{
		dst[d_len + i] = src[i];
		i += 1;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}

static size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	len;

	len = 0;
	while (len < n)
	{
		if (s[len] == '\0')
			break ;
		len += 1;
	}
	return (len);
}
