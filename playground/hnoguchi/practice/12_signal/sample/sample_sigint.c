/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:06:30 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/12 18:00:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct s_token t_token;

typedef struct	s_token {
	char	**argv;
	t_token	*next;
}	t_token;

int	count_argv(char **argv)
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

char	**dup_argv(char **argv)
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

t_token	*new_token(char **argv)
{
	t_token	*new;

	new = calloc(1, sizeof(t_token));
	new->argv = dup_argv(argv);
	return (new);
}

void	add_back(t_token *list, t_token *add)
{
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = add;
}

void	print_result_create_test_token(t_token *token)
{
	while (token != NULL)
	{
		while (*(token->argv) != NULL)
		{
			printf("token->argv : [%s]\n", *(token->argv));
			token->argv += 1;
		}
		token = token->next;
	}
}
	/*
	// case 1
	char *test_1[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	*/
	/*
	// case 2
	char *test_1[] = {
		"notcommand",
		NULL,
	};
	*/
	/*
	// case 3
	char *test_1[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	char *test_2[] = {
		"/usr/bin/grep",
		"multi",
		NULL,
	};
	char *test_3[] = {
		"/usr/bin/wc",
		"-l",
		NULL,
	};
	*/
	/*
	// case 4
	char *test_1[] = {
		"notcommand",
		NULL,
	};
	char *test_2[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	char *test_3[] = {
		"/usr/bin/wc",
		"-l",
		NULL,
	};
	*/
	/*
	// case 5
	char *test_1[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	char *test_2[] = {
		"notcommand",
		NULL,
	};
	char *test_3[] = {
		"/usr/bin/wc",
		"-l",
		NULL,
	};
	*/
	/*
	// case 6
	char *test_1[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	char *test_2[] = {
		"/usr/bin/grep",
		"multi",
		NULL,
	};
	char *test_3[] = {
		"notcommand",
		NULL,
	};
	*/
t_token	*create_test_token(void)
{
	t_token	*token;
	// case 4
	char *test_1[] = {
		"notcommand",
		NULL,
	};
	char *test_2[] = {
		"/bin/cat",
		"Makefile",
		NULL,
	};
	char *test_3[] = {
		"/usr/bin/wc",
		"-l",
		NULL,
	};
	token = new_token(test_1);
	add_back(token, new_token(test_2));
	add_back(token, new_token(test_3));
	return (token);
}

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

void	prepare_pipe(t_token *token, int *next_input, int *output)
{
	if (token->next == NULL)
	{
		return ;
	}
	if (pipe(output) < 0)
	{
		fatal_error("prepare_pipe ; pipe");
	}
	// [process_1] - out_fd -> in_fd - [process_2]
	next_input[0] = output[0];
	next_input[1] = output[1];
}

void	prepare_pipe_child(int *input, int *output)
{
	if (0 < output[0])
	{
		if (close(output[0]) < 0)
		{
			fatal_error("prepare_pipe_chiled ; close 1");
		}
	}
	if (input[0] != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_chiled ; close 2");
		}
		if (dup2(input[0], STDIN_FILENO) < 0)
		{
			fatal_error("prepare_pipe_chiled ; dup2 1");
		}
		if (close(input[0]) < 0)
		{
			fatal_error("prepare_pipe_chiled ; close 3");
		}
	}
	if (output[1] != STDOUT_FILENO)
	{
		if (close(STDOUT_FILENO) < 0)
		{
			fatal_error("prepare_pipe_chiled ; close 3");
		}
		if (dup2(output[1], STDOUT_FILENO) < 0)
		{
			fatal_error("prepare_pipe_chiled ; dup2 2");
		}
		if (close(output[1]) < 0)
		{
			fatal_error("prepare_pipe_chiled ; close 4");
		}
	}
}

void	prepare_pipe_parent(t_token *token, int *input, int *output)
{
	if (input[0] != STDIN_FILENO)
	{
		if (close(input[0]) < 0)
		{
			fatal_error("prepare_pipe_parent ; close 1");
		}
	}
	if (token->next != NULL)
	{
		if (close(output[1]) < 0)
		{
			fatal_error("prepare_pipe_parent ; close 2");
		}
	}
}

pid_t	exec_pipeline(t_token *token, int *input_pipe)
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
		fatal_error("exec_pipeline ; pid < 0");
	}
	else if (pid == 0)
	{
		// child process
		prepare_pipe_child(input_pipe, output_pipe);
		execve(*(token->argv), token->argv, environ);
		fatal_error("exec_pipeline ; execve");
	}
	// parent process
	prepare_pipe_parent(token, input_pipe, output_pipe);
	if (token->next != NULL)
	{
		dprintf(STDERR_FILENO, "command is [%15s] : ", *(token->argv));
		dprintf(STDERR_FILENO, "pid[%d]\n", pid);
		return (exec_pipeline(token->next, next_input));
	}
	dprintf(STDERR_FILENO, "command is [%15s] : ", *(token->argv));
	dprintf(STDERR_FILENO, "pid[%d]\n", pid);
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
		if (wait_result == last_pid)
			status = WEXITSTATUS(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
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
	input_pipe[0] = STDIN_FILENO;
	input_pipe[1] = -1;
	token = create_test_token();
	// print_result_create_test_token(token);
	last_pid = exec_pipeline(token, input_pipe);
	last_status = wait_pipeline(last_pid);
	// dprintf(STDERR_FILENO, "last_pid    : [%d]\n", last_pid);
	// dprintf(STDERR_FILENO, "last_status : [%d]\n", last_status);
	// dprintf(STDOUT_FILENO, "check : STDOUT_FILENO\n");
	while(1)
		;
	exit (EXIT_FAILURE);
}
