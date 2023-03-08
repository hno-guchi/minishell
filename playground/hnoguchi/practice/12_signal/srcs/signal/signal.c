/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 12:39:44 by hnoguchi         ###   ########.fr       */
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

static void	signal_default_handler(int signal)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	initialize_sa(signal, &sa);
}

void	reset_signals(void)
{
	signal_default_handler(SIGINT);
	signal_default_handler(SIGQUIT);
}

static int	event(void)
{
	return (1);
}

void	signal_interrupted_handler(int status)
{
	if (status != SIGINT)
	{
		return ;
	}
	rl_replace_line("", 0);
	rl_done = 1;
}

void	initialize_signals(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_event_hook = event;
	signal(SIGINT, signal_interrupted_handler);
}

/*
int	main(void)
{
	char		*line;
	extern int	_rl_echo_control_chars;

	line = NULL;
	_rl_echo_control_chars = 0;
	rl_event_hook = event;
	signal(SIGINT, signal_interrupted_handler);
	while (1)
	{
		line = readline("sample_signal$ ");
		if (line == NULL)
		{
			break ;
		}
		if (0 < strlen(line))
		{
			add_history(line);
		}
		free(line);
	}
	exit (EXIT_FAILURE);
}
*/
