/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/05 16:40:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_token_word(size_t *size, t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
		{
			*size += 1;
		}
		token = token->next;
	}
}

static char	**create_argv(char *path, t_token *token)
{
	char	**argv;
	size_t	i;
	size_t	size;
	t_token	*head_p;

	i = 1;
	size = 0;
	head_p = token->next;
	count_token_word(&size, token);
	token = head_p;
	argv = ft_calloc(size + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	argv[0] = path;
	while (token != NULL)
	{
		if (token->word != NULL)
		{
			argv[i] = ft_strdup(token->word);
			i += 1;
		}
		token = token->next;
	}
	return (argv);
}

static char	*create_path(char *word)
{
	char	*path;

	path = NULL;
	if (ft_strchr(word, '/') == NULL)
	{
		path = search_path(word);
		if (path == NULL)
		{
			error_message(word, "command not found", 127);
		}
	}
	else
	{
		path = ft_strdup(word);
		if (path == NULL)
		{
			error_message(word, "command not found", 127);
		}
	}
	return (path);
}

static void	do_child(t_node *node, int *pipe_fd, int *prev_fd)
{
	extern char		**environ;
	char			**argv;
	char			*path;

	argv = NULL;
	path = NULL;
	reset_signal_handler();
	prepare_pipe_child(node, pipe_fd, prev_fd);
	redirect_file(node->command);
	path = create_path(node->command->args->word);
	argv = create_argv(path, node->command->args);
	execve(path, argv, environ);
	reset_redirect_command(node->command);
	fatal_error("execve");
}

int	exec_pipeline(t_node *node, int *prev_fd)
{
	pid_t			pid;
	int				pipe_fd[2];

	if (node == NULL)
		return (-1);
	prepare_pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		do_child(node, pipe_fd, prev_fd);
	}
	else
	{
		prepare_pipe_parent(pipe_fd);
		exec_pipeline(node->next, pipe_fd);
		if (pipe_fd[0] != STDIN_FILENO)
			if (close(pipe_fd[0]) < 0)
				assert_error("close");
	}
	return (pid);
}
