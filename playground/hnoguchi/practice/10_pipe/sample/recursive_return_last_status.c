/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_return_last_status.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:53:45 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 16:18:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	recursive_sum(int num)
{
	if (num == 100)
	{
		return (-1);
	}
	num++;
	if (num < 100)
	{
		// printf("[%d]-> ", num);
		return (recursive_sum(num));
		printf("[%d]-> ", num);
	}
	return (num);
}

int	main(void)
{
	int	result = recursive_sum(1);

	printf("result : [%d]\n", result);
}
