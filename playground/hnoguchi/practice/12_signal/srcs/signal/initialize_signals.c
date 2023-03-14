/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:39:49 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 18:08:12 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	initialize_signals(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
	{
		rl_event_hook = readline_event_handler;
	}
	set_signals_receiver();
	signal_ignore_handler(SIGQUIT);
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
