/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xperror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 20:33:56 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xperror(const char *location)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(location);
}
