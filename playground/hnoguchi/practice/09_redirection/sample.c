/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:56:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/07 20:03:42 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ~$ ./a.out > result.log 2 > error.log
 */
#include <unistd.h>

int	main(void)
{
	write(1, "Hello", 5);
	write(2, "error", 5);
	return (0);
}
