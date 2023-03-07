/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:32:11 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/07 11:25:57 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * 2.4.10 Utility Functions
 * https://tiswww.case.edu/php/chet/readline/readline.html#Utility-Functions
 * 
 * void	rl_replace_line (const char *text, int clear_undo);
 *
 * Replace the contents of rl_line_buffer with text.
 * The point and mark are preserved, if possible.
 * If clear_undo is non-zero, the undo list associated with the current line is cleared.
 *
 * signals.c
 * https://github.com/walterschell/libreadline/blob/cmake/signals.c
 * L.105
 * If non-zero, print characters corresponding to received signals as long as the user has indicated his desire to do so
 * (_rl_echo_control_chars).
 *
 * 2.3 Readline Variables
 * https://tiswww.case.edu/php/chet/readline/readline.html#Readline-Variables
 *
 * int rl_done;
 * Setting this to a non-zero value causes Readline to return the current line immediately.
 * Readline will set this variable when it has read a key sequence bound to accept-line and is about to return the line to the caller.
 *
 * rl_hook_func_t * rl_event_hook;
 * If non-zero, this is the address of a function to call periodically when Readline is waiting for terminal input.
 * By default, this will be called at most ten times a second if there is no keyboard input.
 *
 */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	event(void)
{
	return (1);
}

void	handler(int status)
{

	if (status != SIGINT)
	{
		return ;
	}
	// rl_replace_line("Catch [SIGINT]", 0);
	rl_replace_line("", 0);
	// rl_redisplay();
	rl_done = 1;
}

int	main(void)
{
	char	*line;
	extern int	_rl_echo_control_chars;

	line = NULL;
	_rl_echo_control_chars = 0;
	rl_event_hook = event;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("sample$ ");
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
