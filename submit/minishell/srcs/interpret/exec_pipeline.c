/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/27 11:37:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_child(t_node *node)
{
	char			**env;
	char			**argv;
	char			*path;

	env = NULL;
	argv = NULL;
	path = NULL;
	redirect_file(node->command);
	env = create_env();
	path = create_path(node->command->args->word);
	argv = create_argv(path, node->command->args);
	execve(path, argv, env);
	reset_redirect_command(node->command);
	frees_env(env);
	frees_argv(argv);
	fatal_error("execve");
}

int	exec_pipeline(t_node *node, int *input_pipe)
{
	pid_t			pid;
	int				next_input_pipe[2];
	int				output_pipe[2];

	if (node == NULL)
		return (-1);
	prepare_pipe(node, next_input_pipe, output_pipe);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		set_signals_default();
		prepare_pipe_child(input_pipe, output_pipe);
		if (is_builtin(node->command->args->word))
			exit(exec_builtin(node));
		else
			do_child(node);
	}
	set_signals_ignore();
	close_pipe_parent(node, input_pipe, output_pipe);
	if (node->next != NULL)
		return (exec_pipeline(node->next, next_input_pipe));
	return (pid);
}
