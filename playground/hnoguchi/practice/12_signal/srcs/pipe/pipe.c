/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:03:58 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/09 12:10:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(t_node *node, int *next_input, int *output)
{
	next_input[0] = STDIN_FILENO;
	next_input[1] = -1;
	output[0] = -1;
	output[1] = STDOUT_FILENO;
	if (node->next == NULL)
	{
		return ;
	}
	if (pipe(output) < 0)
	{
		fatal_error("pipe");
	}
	next_input[0] = output[0];
	next_input[1] = output[1];
}

void	connect_pipe_stdin_fileno(int *pipe)
{
	if (close(STDIN_FILENO) < 0)
	{
		fatal_error("close 1");
	}
	if (dup2(*pipe, STDIN_FILENO) < 0)
	{
		fatal_error("dup2");
	}
	if (close(*pipe) < 0)
	{
		fatal_error("close 2");
	}
}

void	connect_pipe_stdout_fileno(int *pipe)
{
	if (close(STDOUT_FILENO) < 0)
	{
		fatal_error("close 3");
	}
	if (dup2(*pipe, STDOUT_FILENO) < 0)
	{
		fatal_error("dup2");
	}
	if (close(*pipe) < 0)
	{
		fatal_error("close 4");
	}
}

void	prepare_pipe_child(int *input, int *output)
{
	if (0 < output[0])
	{
		if (close(output[0]) < 0)
		{
			fatal_error("close 5");
		}
	}
	if (input[0] != STDIN_FILENO)
	{
		connect_pipe_stdin_fileno(&input[0]);
	}
	if (output[1] != STDOUT_FILENO)
	{
		connect_pipe_stdout_fileno(&output[1]);
	}
}

void	prepare_pipe_parent(t_node *node, int *input, int *output)
{
	if (input[0] != STDIN_FILENO)
	{
		if (close(input[0]) < 0)
		{
			fatal_error("close 6");
		}
	}
	if (node->next != NULL)
	{
		if (close(output[1]) < 0)
		{
			fatal_error("close 7");
		}
	}
}
