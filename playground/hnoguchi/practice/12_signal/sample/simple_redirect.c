/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:48:13 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 14:12:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int	event(void)
{
	return (1);
}

static void	signal_interrupted_handler(int status)
{
	if (status != SIGINT)
	{
		return ;
	}
	rl_replace_line("", 0);
	rl_done = 1;
}

static void	simple_redirect(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		write(STDOUT_FILENO, line, strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
	if (line != NULL)
		free(line);
}

int	main(void)
{
	char	*line;
	extern int	_rl_echo_control_chars;

	line = NULL;
	_rl_echo_control_chars = 0;
	rl_event_hook = event;
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
