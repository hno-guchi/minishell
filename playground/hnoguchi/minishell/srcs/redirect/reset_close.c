/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:32:21 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/21 16:12:15 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_close(int	*target_fd)
{
	if (*target_fd < 0)
	{
		return ;
	}
	if (close(*target_fd) < 0)
	{
		fatal_error("reset_close");
	}
	if (*target_fd != STDIN_FILENO && *target_fd != STDOUT_FILENO)
	{
		*target_fd = -1;
	}
}
