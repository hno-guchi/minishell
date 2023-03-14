/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_sa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 17:24:55 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_sa(int signal, struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal, sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}
