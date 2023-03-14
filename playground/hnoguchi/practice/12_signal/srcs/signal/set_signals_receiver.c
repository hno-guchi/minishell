/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals_receiver.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 17:31:38 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_interrupted_handler(int status)
{
	g_minishell.sig = status;
}

static void	signal_interrupted_receiver(int signal)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = signal_interrupted_handler;
	sa.sa_flags = 0;
	initialize_sa(signal, &sa);
}

void	set_signals_receiver(void)
{
	signal_interrupted_receiver(SIGINT);
}
