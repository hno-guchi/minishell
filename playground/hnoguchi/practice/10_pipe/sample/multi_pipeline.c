/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:52:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/23 15:13:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Create muliti pipeline
 * ~$ cat pipeline.c | grep "a" | wc -l
 */
#include "multi_pipeline.h"

void	prepare_pipeline_child(t_pipe_fd *list, int *pipe_fd, int *prev_fd)
{
	if (prev_fd[0] != STDIN_FILENO)
	{
		if (close(STDIN_FILENO) < 0)
		{
			fatal_error("recursive_do_pipeline", "close(stdin);");
		}
		if (dup2(prev_fd[0], STDIN_FILENO) < 0)
		{
			fatal_error("recursive_do_pipeline", "dup2");
		}
		if (close(prev_fd[0]) < 0)
		{
			fatal_error("recursive_do_pipeline", "close");
		}
	}
	if (close(pipe_fd[0]) < 0)
	{
		fatal_error("recursive_do_pipeline", "close(pipe_fd[0]); child");
	}
	if (list->next != NULL)
	{
		if (pipe_fd[1] != STDOUT_FILENO)
		{
			if (close(STDOUT_FILENO) < 0)
			{
				fatal_error("recursive_do_pipeline", "close stdout");
			}
			if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			{
				fatal_error("recursive_do_pipeline", "dup2");
			}
		}
	}
	if (close(pipe_fd[1]) < 0)
	{
		fatal_error("recursive_do_pipeline", "close");
	}
}

void	recursive_do_pipeline(t_pipe_fd *list, int *prev_fd)
{
	extern char	**environ;
	int			pipe_fd[2];
	pid_t		pid;

	if (list == NULL)
	{
		return ;
	}
	if (pipe(pipe_fd) < 0)
	{
		fatal_error("recursive_do_pipeline", "pipe");
	}
	pid = fork();
	if (pid < 0)
	{
		fatal_error("recursive_do_pipeline", "fork");
	}
	else if (pid == 0)
	{
		// child process
		prepare_pipeline_child(list, pipe_fd, prev_fd);
		/*
		if (prev_fd[0] != STDIN_FILENO)
		{
			if (close(STDIN_FILENO) < 0)
			{
				fatal_error("recursive_do_pipeline", "close(stdin);");
			}
			if (dup2(prev_fd[0], STDIN_FILENO) < 0)
			{
				fatal_error("recursive_do_pipeline", "dup2");
			}
			if (close(prev_fd[0]) < 0)
			{
				fatal_error("recursive_do_pipeline", "close");
			}
		}
		if (close(pipe_fd[0]) < 0)
		{
			fatal_error("recursive_do_pipeline", "close(pipe_fd[0]); child");
		}
		if (list->next != NULL)
		{
			if (pipe_fd[1] != STDOUT_FILENO)
			{
				if (close(STDOUT_FILENO) < 0)
				{
					fatal_error("recursive_do_pipeline", "close stdout");
				}
				if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
				{
					fatal_error("recursive_do_pipeline", "dup2");
				}
			}
		}
		if (close(pipe_fd[1]) < 0)
		{
			fatal_error("recursive_do_pipeline", "close");
		}
		*/
		execve(list->argv[0], list->argv, environ);
		fatal_error("recursive_do_pipeline", "execve");
	}
	else
	{
		// Parent process
		if (close(pipe_fd[1]) < 0)
		{
			fatal_error("recursive_do_pipeline", "close(pipe_fd[1]); parent");
		}
		if (wait(NULL) < 0)
		{
			fatal_error("recursive_do_pipeline", "wait(NULL); parent");
		}
		// print_result_execve(pipe_fd[0]);
		recursive_do_pipeline(list->next, pipe_fd);
		if (close(pipe_fd[0]) < 0)
		{
			fatal_error("recursive_do_pipeline", "close(pipe_fd[0]); parent");
		}
	}
}

int	main(int argc, char **argv)
{
	t_pipe_fd *list;
	int			pipe_fd[2];

	list = NULL;
	pipe_fd[0] = STDIN_FILENO;
	pipe_fd[1] = STDOUT_FILENO;
	if (argc < 2)
	{
		fatal_error("main", "Not args...");
	}
	list = create_pipe_fd_list(argc, argv);
	// print_result_list(&list);
	recursive_do_pipeline(list, pipe_fd);
	frees_list(&list);
	// dprintf(STDOUT_FILENO, "STDOUT_FILENO is [%d]\n", STDOUT_FILENO);
	// while(1)
	// 	;
	system("leaks -q multi_pipeline");
	exit(EXIT_SUCCESS);
}
