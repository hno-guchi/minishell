/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals_ignore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 17:28:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ignore_handler(int signal)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	initialize_sa(signal, &sa);
}

void	set_signals_ignore(void)
{
	signal_ignore_handler(SIGINT);
}
