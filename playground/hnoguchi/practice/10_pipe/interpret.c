/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 17:54:30 by hnoguchi         ###   ########.fr       */
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
	prepare_pipe(node, pipe_fd);
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
		path = create_path(node->command->args->word);
		argv = create_argv(path, node->command->args);
		execve(path, argv, environ);
		reset_redirect_command(node->command);
		fatal_error("interpret: execve");
	}
	// Parent process
	prepare_pipe_parent(node, pipe_fd);
	if (node->next != NULL)
	{
		// dprintf(STDERR_FILENO, "node->command->args->word : [%s]\n", node->command->args->word);
		// dprintf(STDERR_FILENO, "return(pid); [%d]\n\n", pid);
		return (exec_pipeline(node->next, pipe_fd));
		// if (pipe_fd[0] != STDIN_FILENO)
		// {
		// 	if (close(pipe_fd[0]) < 0)
		// 	{
		// 		fatal_error("exec_pipeline : close");
		// 	}
		// }
	}	
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	status = 0;
	wstatus = 0;
	while (1)
	{
		wait_result = wait(&wstatus);
	dprintf(STDERR_FILENO, "[0] : last_pid : [%d]\n", last_pid);
	dprintf(STDERR_FILENO, "wait_result : [%d]\n", wait_result);
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
			else if (errno == EINTR)
			{
				continue ;
			}
			else
			{
				fatal_error("wait");
			}
		}
		dprintf(STDERR_FILENO, "[1] : last_pid : [%d]\n\n", last_pid);
	}
	return (status);
}

int	interpret(t_node *node)
{
	int		status;
	int		pipe_fd[2];
	pid_t	last_pid;

	status = 0;
	pipe_fd[0] = STDIN_FILENO;
	pipe_fd[1] = STDOUT_FILENO;
	if (open_redir_file(node) < 0)
	{
		return (ERROR_OPEN_REDIR);
	}
	last_pid = exec_pipeline(node, pipe_fd);
	dprintf(STDERR_FILENO, "last_pid; [%d]\n\n", last_pid);
	status = wait_pipeline(last_pid);
	dprintf(STDERR_FILENO, "return (status); [%d]\n\n", status);
	return (status);
}
