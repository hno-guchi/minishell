/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:21:42 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 16:44:05 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

void	ignore_signal_handler(int signal_number)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sa_initialize(signal_number, &sa);
}

void	sigint_signal_handler(int signal_number, siginfo_t *info,
		void *ucontext_ap)
{
	(void)info;
	(void)ucontext_ap;
	if (signal_number == SIGINT)
	{
		g_minishell.sig = signal_number;
	}
}

void	sigint_signal_receiver(void handler(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sa_initialize(SIGINT, &sa);
}

void	setup_signals(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
	{
		rl_event_hook = check_signal;
	}
	ignore_signal_handler(SIGQUIT);
	sigint_signal_receiver(sigint_signal_handler);
}
