/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:21:42 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 16:40:45 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sa_initialize(int signal_number, struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal_number, sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}
