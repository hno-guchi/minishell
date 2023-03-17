/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:20:47 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/11 16:23:52 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	if (lst == NULL)
		return (0);
	i = 1;
	while (lst->next != NULL && i < INT_MAX)
	{
		lst = lst->next;
		i += 1;
	}
	if (i == INT_MAX && lst->next != NULL)
		return (-1);
	return (i);
}
