/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 15:18:06 by hnoguchi         ###   ########.fr       */
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

void	signal_default_handler(int signal)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	initialize_sa(signal, &sa);
}

void	reset_signals(void)
{
	signal_default_handler(SIGINT);
}

static int	readline_event_handler(void)
{
	if (g_minishell.sig == 0)
	{
		return (0);
	}
	else if (g_minishell.sig == SIGINT)
	{
		g_minishell.sig = 0;
		g_minishell.readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	signal_interrupted_handler(int status)
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

void	initialize_signals(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
	{
		rl_event_hook = readline_event_handler;
	}
	signal_interrupted_receiver(SIGINT);
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
