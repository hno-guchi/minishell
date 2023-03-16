/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:42:03 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/01 14:01:42 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		(void)write(fd, "(null)", sizeof(char) * 6);
	else
	{
		len = ft_strlen(s);
		(void)write(fd, s, len);
	}
	return ;
}
