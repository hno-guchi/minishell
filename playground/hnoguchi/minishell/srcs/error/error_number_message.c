/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_number_message.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/18 17:41:01 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_number_message(const char *word, int num)
{
	if (num == -1)
	{
		error_message(word, "is a directory", 126);
	}
	else if (num == 2)
	{
		error_message(word, strerror(num), 127);
	}
	else if (num == 13)
	{
		error_message(word, strerror(num), 126);
	}
	else if (num == 20)
	{
		error_message(word, strerror(num), 126);
	}
	else
	{
		error_message(word, strerror(num), 127);
	}
}
