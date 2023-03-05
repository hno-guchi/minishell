/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 13:32:44 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	frees_argv(char **argv)
{
	while (*argv != NULL)
	{
		free(*argv);
		argv++;
	}
}

char	**create_argv(char *path, t_token *token)
{
	char	**argv;
	size_t	i;
	size_t	size;
	t_token	*head_p;

	i = 1;
	size = 0;
	head_p = token->next;
	while (token != NULL)
	{
		size += 1;
		token = token->next;
	}
	token = head_p;
	argv = calloc(size + 1, sizeof(char *));
	if (argv == NULL)
	{
		fatal_error("calloc");
	}
	argv[0] = path;
	while (token != NULL)
	{
		argv[i] = strdup(token->word);
		token = token->next;
		i += 1;
	}
	return (argv);
}

char	*create_path(char *word)
{
	char	*path;

	path = NULL;
	if (strchr(word, '/') == NULL)
	{
		path = search_path(word);
		if (path == NULL)
		{
			error_message(path, "command not found", 127);
		}
	}
	else
	{
		path = strdup(word);
		if (path == NULL)
		{
			error_message(path, "command not found", 127);
		}
	}
	return (path);
}

int	exec_pipeline(t_node *node, int *prev_fd)
{
	extern char		**environ;
	char			**argv;
	char			*path;
	pid_t			pid;
	int				pipe_fd[2];

	if (node == NULL)
	{
		return (-1);
	}
	prepare_pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		fatal_error("interpret: fork");
	}
	else if (pid == 0)
	{
		// child process
		prepare_pipe_child(node, pipe_fd, prev_fd);
		redirect_file(node->command);
		// print_result_open_redir(node->command->redirects->args, "[AFTER] redirect_file();");
		path = create_path(node->command->args->word);
		argv = create_argv(path, node->command->args);
		// print_result_create_argv(argv);
		execve(path, argv, environ);
		reset_redirect_command(node->command);
		// frees_argv(argv);
		// free(argv);
		fatal_error("interpret: execve");
	}
	else
	{
		// Parent process
		// print_result_open_redir(node->command->redirects->args, "[BEFORE] prepare_pipe_parent();");
		prepare_pipe_parent(pipe_fd);
		// print_result_open_redir(node->command->redirects->args, "[AFTER] prepare_pipe_parent();");
		// if (wait(NULL) < 0)
		// {
		// 	fatal_error("prepare_pipe_parent : wait");
		// }
		// print_result_open_redir(node->command->redirects->args, "[AFTER] execve();");
		// if (node->next != NULL)
		// {
		// 	return (exec_pipeline(node->next, pipe_fd));
		// }
		exec_pipeline(node->next, pipe_fd);
		if (pipe_fd[0] != STDIN_FILENO)
		{
			if (close(pipe_fd[0]) < 0)
			{
				fatal_error("exec_pipeline : close");
			}
		}
		// dprintf(STDERR_FILENO, "close(node->pipe_fd[0]); [%d]\n", node->pipe_fd[0]);
	}
	dprintf(STDERR_FILENO, "return(pid); [%d]\n", pid);
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
			{
				break ;
			}
		}
	}
	return (status);
}

/*
int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	// if (open_redir_file(node) < 0)
	// {
	// 	return (ERROR_OPEN_REDIR);
	// }
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}
*/

int	interpret(t_node *node)
{
	int		status;
	int		pipe_fd[2];
	pid_t	last_pid;

	status = 0;
	pipe_fd[0] = STDIN_FILENO;
	pipe_fd[1] = STDOUT_FILENO;
	// status = exec(node);
	// if (open_redir_file(node) < 0)
	// {
	// 	return (ERROR_OPEN_REDIR);
	// }
	last_pid = exec_pipeline(node, pipe_fd);
	dprintf(STDERR_FILENO, "last_pid; [%d]\n", last_pid);
	status = wait_pipeline(last_pid);
	dprintf(STDERR_FILENO, "return (status); [%d]\n", status);
	return (status);
}
