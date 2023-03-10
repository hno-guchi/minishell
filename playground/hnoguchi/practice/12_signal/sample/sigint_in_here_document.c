/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_in_here_document.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:48:13 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 09:26:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	g_signal_interrupted;
int		g_catch_signal;

static int	readline_event_handler(void)
{
	if (g_catch_signal != SIGINT)
	{
		return (1);
	}
	g_signal_interrupted = true;
	g_catch_signal = 0;
	rl_replace_line("", 0);
	rl_done = 1;
	return (1);
}

static void	signal_interrupted_handler(int status)
{
	if (status != SIGINT)
	{
		return ;
	}
	g_catch_signal = status;
}

static void	simple_redirect(void)
{
	char	*line;

	line = NULL;
	g_signal_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if (g_signal_interrupted == true)
		{
			break ;
		}
		write(STDOUT_FILENO, line, strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
	if (line != NULL)
	{
		free(line);
	}
}

int	main(void)
{
	char	*line;
	extern int	_rl_echo_control_chars;

	line = NULL;
	_rl_echo_control_chars = 0;
	rl_event_hook = readline_event_handler;
	signal(SIGINT, signal_interrupted_handler);
	while (1)
	{
		line = readline("simple_redirect$ ");
		if (line == NULL)
		{
			break ;
		}
		if (0 < strlen(line))
		{
			add_history(line);
		}
		if (strcmp(line, "<< EOF") == 0)
		{
			simple_redirect();
		}
		free(line);
	}
	exit(EXIT_FAILURE);
}
