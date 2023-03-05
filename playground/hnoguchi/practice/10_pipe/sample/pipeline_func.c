/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:52:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/22 11:14:50 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multi_pipeline.h"

void	fatal_error(char *location, char *message)
{
	dprintf(STDERR_FILENO, "%s: %s\n", location, message);
	exit(EXIT_FAILURE);
}

int	my_cat(char **read_str, int pipe_fd)
{
	char	buf[BUF_SIZE];
	char	*temp_str;
	int		read_size;
	int		str_size;

	temp_str = NULL;
	read_size = 0;
	str_size = 0;
	read_size = read(pipe_fd, buf, BUF_SIZE);
	while (read_size != 0)
	{
		if (read_size < 0)
		{
			fatal_error("my_cat", "read");
		}
		if (str_size == 0)
		{
			str_size += read_size;
			temp_str = calloc(read_size + 1, sizeof(char));
			if (temp_str == NULL)
			{
				fatal_error("my_cat", "calloc");
			}
			strlcpy(temp_str, buf, read_size + 1);
			*read_str = temp_str;
		}
		else
		{
			str_size += read_size;
			temp_str = calloc(str_size + 1, sizeof(char));
			if (temp_str == NULL)
			{
				fatal_error("my_cat", "calloc");
			}
			strlcpy(temp_str, *read_str, str_size + 1);
			strlcat(temp_str, buf, str_size + 1);
			free(*read_str);
			*read_str = temp_str;
		}
		read_size = read(pipe_fd, buf, BUF_SIZE);
	}
	return (str_size + 1);
}

// char	**create_argv(char *command, char *str)
char	**create_argv(char *command)
{
	char	*head_p_command;
	char	**new_argv;
	char	**head_p_argv;
	int		argv_size;

	if (command == NULL)
	{
		return (NULL);
	}
	head_p_command = command;
	argv_size = 1;
	/*
	if (str != NULL)
	{
		argv_size += 1;
	}
	*/
	while (*command != '\0')
	{
		if (*command == ' ')
		{
			argv_size += 1;
		}
		command++;
	}
	command = head_p_command;
	// dprintf(STDOUT_FILENO, "argv_size == [%d]\n", argv_size);
	new_argv = calloc(argv_size + 1, sizeof(char *));
	if (new_argv == NULL)
	{
		fatal_error("create_argv", "calloc");
	}
	head_p_argv = new_argv;
	if (1 < argv_size)
	{
		while (*command != '\0')
		{
			while (*command != ' ' && *command != '\0')
			{
				command++;
			}
			*new_argv = strndup(head_p_command, (command - head_p_command));
			// dprintf(STDOUT_FILENO, "new_argv == [%s]\n", *new_argv);
			if (*new_argv == NULL)
			{
				fatal_error("create_argv", "strndup");
			}
			new_argv++;
			if (*command == ' ')
			{
				command++;
			}
			head_p_command = command;
		}
		/*
		if (str != NULL)
		{
			*new_argv = strdup(str);
		}
		*/
		new_argv = head_p_argv;
	}
	else
	{
		*new_argv = strdup(command);
		/*
		if (str != NULL)
		{
			new_argv++;
			*new_argv = strdup(str);
		}
		new_argv = head_p_argv;
		*/
	}
	// free(str);
	// str = NULL;
	return (new_argv);
}

t_pipe_fd	*create_pipe_fd_list(int size, char **argv)
{
	t_pipe_fd	head;
	t_pipe_fd	*current_node;

	head.next = NULL;
	current_node = &head;
	while (1 < size)
	{
		size -= 1;
		argv++;
		current_node->next = calloc(1, sizeof(t_pipe_fd));
		if (current_node->next == NULL)
		{
			fatal_error("create_pipe_fd_list", "calloc");
		}
		current_node->next->argv = create_argv(*argv);
		current_node->next->pipe_fd[0] = STDIN_FILENO;
		current_node->next->pipe_fd[1] = STDOUT_FILENO;
		current_node = current_node->next;
	}
	return (head.next);
}

void	frees_argv(char **argv)
{
	char	**head_p;

	head_p = argv;
	while (*argv != NULL)
	{
		free(*argv);
		argv++;
	}
	free(*argv);
	free(head_p);
}

void	frees_list(t_pipe_fd **list)
{
	t_pipe_fd	*next;

	next = NULL;
	while (*list != NULL)
	{
		next = (*list)->next;
		frees_argv((*list)->argv);
		free(*list);
		*list = next;
	}
}

void	print_result_argv(char **argv)
{
	dprintf(STDOUT_FILENO, "-----------------------\n");
	while (*argv != NULL)
	{
		dprintf(STDOUT_FILENO, "*argv == [%s]\n", *argv);
		argv++;
	}
	dprintf(STDOUT_FILENO, "*argv == [%s]\n", *argv);
	dprintf(STDOUT_FILENO, "-----------------------\n\n");
}

void	print_result_list(t_pipe_fd **list)
{
	t_pipe_fd	*head_p;

	head_p = *list;
	while (*list != NULL)
	{
		print_result_argv((*list)->argv);
		*list = (*list)->next;
	}
	*list = head_p;
}

void	print_result_execve(int input_fd)
{
	int	str_size;
	char	buf[BUF_SIZE];

	str_size = read(input_fd, buf, BUF_SIZE);
	while (0 != str_size)
	{
		if (str_size < 0)
		{
			fatal_error("print_result_execve", "read");
		}
		write(STDOUT_FILENO, buf, str_size);
		str_size = read(input_fd, buf, BUF_SIZE);
	}
	if (close(input_fd) < 0)
	{
		fatal_error("print_result_execve", "close(input_fd);");
	}
}

/*
// test main(); create_argv();
int	main(int argc, char **argv)
{
	char	**my_argv;
	// char	**head_p;

	if (argc < 2)
	{
		fatal_error("test_main", "Not args...");
	}
	while (*argv != NULL)
	{
		my_argv = create_argv(*argv);
		print_result_argv(my_argv);
		frees_argv(my_argv);
		argv++;
	}
	system("leaks -q a.out");
}
*/
