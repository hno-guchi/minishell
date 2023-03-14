/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_signal_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:21:42 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 12:12:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	default_signal_handler(int signal_number)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	sa_initialize(signal_number, &sa);
}

void	reset_signal_handler(void)
{
	default_signal_handler(SIGINT);
	// default_signal_handler(SIGQUIT);
}
