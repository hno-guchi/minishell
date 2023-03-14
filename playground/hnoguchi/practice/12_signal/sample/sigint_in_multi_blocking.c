/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_in_multi_blocking.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:45:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 15:49:56 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_token	t_token;

typedef struct s_token	{
	char	**argv;
	t_token	*next;
}	t_token;

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

static void	set_signal_ignore(int signal)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal, &sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}

static void	set_signal_default(int signal)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal, &sa, NULL) == -1)
	{
		fatal_error("sigaction");
	}
}

static int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (*argv != NULL)
	{
		count += 1;
		argv += 1;
	}
	return (count);
}

static char	**dup_argv(char **argv)
{
	char	**dup;
	char	**head_p;
	int		count;

	count = count_argv(argv);
	dup = calloc(count + 1, sizeof(char *));
	head_p = dup;
	while (*argv != NULL)
	{
		*dup = strdup(*argv);
		dup += 1;
		argv += 1;
	}
	return (head_p);
}

static t_token	*new_token(char **argv)
{
	t_token	*new;

	new = calloc(1, sizeof(t_token));
	new->argv = dup_argv(argv);
	return (new);
}

static void	add_back_token(t_token *list, t_token *add_token)
{
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = add_token;
}

/*
static void	print_result_create_test_token(t_token *token)
{
	while (token != NULL)
	{
		while (*(token->argv) != NULL)
		{
			dprintf(STDERR_FILENO, "token->argv : [%s]\n", *(token->argv));
			token->argv += 1;
		}
		token = token->next;
	}
}
*/

t_token	*create_test_token(void)
{
	t_token	*token;
	char *test_1[] = {
		"/bin/cat",
		NULL,
	};
	char *test_2[] = {
		"/bin/cat",
		NULL,
	};
	char *test_3[] = {
		"/bin/ls",
		NULL,
	};
	token = new_token(test_1);
	add_back_token(token, new_token(test_2));
	add_back_token(token, new_token(test_3));
	return (token);
}

static void	prepare_pipe(t_token *token, int *next_input, int *output)
{
	if (token->next == NULL)
	{
		return ;
	}
	if (pipe(output) < 0)
	{
		fatal_error("prepare_pipe");
	}
	next_input[0] = output[0];
	next_input[1] = output[1];
}

static void	prepare_pipe_child(int *input, int *output)
{
	if (0 < output[0])
	{
		if (close(output[0]) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
	}
	if (input[0] != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
		if (dup2(input[0], STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
		if (close(input[0]) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
	}
	if (output[1] != STDOUT_FILENO)
	{
		if (close(STDOUT_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
		if (dup2(output[1], STDOUT_FILENO) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
		if (close(output[1]) < 0)
		{
			fatal_error("prepare_pipe_child");
		}
	}
}

static void	prepare_pipe_parent(t_token *token, int *input, int *output)
{
	if (input[0] != STDIN_FILENO)
	{
		if (close(input[0]) < 0)
		{
			fatal_error("prepare_pipe_parent");
		}
	}
	if (token->next != NULL)
	{
		if (close(output[1]) < 0)
		{
			fatal_error("prepare_pipe_parent");
		}
	}
}

static pid_t	exec_pipeline(t_token *token, int *input_pipe)
{
	extern char	**environ;
	pid_t		pid;
	int			next_input[2];
	int			output_pipe[2];

	if (token == NULL)
	{
		return (-1);
	}
	next_input[0] = STDIN_FILENO;
	next_input[1] = -1;
	output_pipe[0] = -1;
	output_pipe[1] = STDOUT_FILENO;
	prepare_pipe(token, next_input, output_pipe);
	pid = fork();
	if (pid < 0)
	{
		fatal_error("fork");
	}
	else if (pid == 0)
	{
		// Child process
		set_signal_default(SIGINT);
		prepare_pipe_child(input_pipe, output_pipe);
		execve(*(token->argv), token->argv, environ);
		fatal_error("execve");
	}
	// Parent process
	set_signal_ignore(SIGINT);
	prepare_pipe_parent(token, input_pipe, output_pipe);
	if (token->next != NULL)
	{
		// dprintf(STDERR_FILENO, "token->argv[%15s] : ", *(token->argv));
		// dprintf(STDERR_FILENO, "pid[%d]\n", pid);
		return (exec_pipeline(token->next, next_input));
	}
	// dprintf(STDERR_FILENO, "token->argv[%15s] : ", *(token->argv));
	// dprintf(STDERR_FILENO, "pid[%d]\n", pid);
	return (pid);
}

static int	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		status_location;
	int		signal_number;
	pid_t	wait_result_pid;

	status = 0;
	status_location = 0;
	signal_number = 0;
	while (1)
	{
		wait_result_pid = wait(&status_location);
		if (wait_result_pid == last_pid)
		{
			if (WIFEXITED(status_location))
			{
				// dprintf(STDERR_FILENO, "WIFEXITED(); == true;\n");
				status = WEXITSTATUS(status_location);
			}
			else if (WIFSIGNALED(status_location))
			{
				// dprintf(STDERR_FILENO, "WIFSIGNALED(); == true;\n");
				signal_number = WTERMSIG(status_location);
				// if (signal_number == SIGINT)
				// {
				// 	dprintf(STDERR_FILENO, "\ncatch SIGINT\n");
				// }
				status = 128 + signal_number;
			}
			else
			{
				fatal_error("wait");
			}
		}
		else if (wait_result_pid < 0)
		{
			if (errno == ECHILD)
			{
				break ;
			}
		}
		else
		{
			if (WIFSIGNALED(status_location))
			{
				// dprintf(STDERR_FILENO, "WIFSIGNALED(); == true;\n");
				signal_number = WTERMSIG(status_location);
				if (signal_number == SIGINT)
				{
					dprintf(STDERR_FILENO, "\ncatch SIGINT\n");
				}
			}
		}
	}
	if (signal_number == SIGINT)
	{
		dprintf(STDERR_FILENO, "status == [%d]\n", status);
	}
	return (status);
}

int	main(void)
{
	int		last_status;
	pid_t	last_pid;
	t_token	*token;
	int		input_pipe[2];

	last_status = 0;
	token = create_test_token();
	input_pipe[0] = STDIN_FILENO;
	input_pipe[1] = -1;
	// while (1)
	// {
		// print_result_create_test_token(token);
		last_pid = exec_pipeline(token, input_pipe);
		last_status = wait_pipeline(last_pid);
		// dprintf(STDERR_FILENO, "last_pid    : [%d]\n", last_pid);
		// dprintf(STDERR_FILENO, "last_status : [%d]\n", last_status);
		// dprintf(STDOUT_FILENO, "check : STDOUT_FILENO\n");
	// } 
	return (last_status);
}
