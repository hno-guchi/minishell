/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 18:17:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default_handler(int signal)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	initialize_sa(signal, &sa);
}

void	set_signals_default(void)
{
	signal_default_handler(SIGINT);
	signal_default_handler(SIGQUIT);
}
