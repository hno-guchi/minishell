/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:25:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:04:54 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_uc;
	unsigned char		*src_uc;

	if (dst == src || len == 0)
		return (dst);
	i = 1;
	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	if (src < dst)
	{
		while (i <= len)
		{
			dst_uc[len - i] = src_uc[len - i];
			i += 1;
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
