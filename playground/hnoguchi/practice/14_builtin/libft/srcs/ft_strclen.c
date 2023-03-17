/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:06:02 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/10/13 05:54:29 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *s, const char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
	{
		len += 1;
	}
	if (s[len] == '\0')
	{
		return (0);
	}
	return (len);
}
