/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:32:53 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/16 11:21:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 480

void	err_exit(char *location, char *message)
{
	dprintf(STDERR_FILENO, "%s: %s\n", location, message);
	exit(EXIT_FAILURE);
}

int	here_document(void)
{
	int		pfd[2];
	char	*line;

	line = NULL;
	if (pipe(pfd) == -1)
	{
		err_exit("here_document();", "pipe(pfd)");
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if(strcmp(line, "EOF") == 0)
		{
			free(line);
			break ;
		}
		if (write(pfd[1], line,strlen(line)) == -1)
		{
			err_exit("here_document();", "write(pfd[1], line, strlen(line));");
		}
		if (write(pfd[1], "\n", 1) == -1)
		{
			err_exit("here_document();", "write(pfd[1], \"\\n\", 1);");
		}
		free(line);
	}
	if (close(pfd[1]) == -1)
	{
		err_exit("here_document();", "close(pfd[1])");
	}
	return (pfd[0]);
}

void	my_cat(int pfd)
{
	char	buf[BUF_SIZE];
	char	*str;
	char	*temp;
	int		read_size;
	int		str_size;

	str = NULL;
	temp = NULL;
	read_size = 0;
	str_size = 0;
	while ((read_size = read(pfd, buf, BUF_SIZE)) != 0)
	{
		if (read_size == -1)
		{
			free(str);
			err_exit("my_cat();", "read");
		}
		str_size = read_size;
		if (str != NULL)
		{
			str_size += strlen(str);
			temp = calloc(str_size + 1, sizeof(char));
			if (temp == NULL)
			{
				err_exit("my_cat();", "calloc 1");
			}
			strlcpy(temp, str, str_size + 1);
			strlcat(temp, buf, str_size + 1);
			free(str);
			str = temp;
		}
		else
		{
			str = calloc(str_size + 1, sizeof(char));
			if (str == NULL)
			{
				err_exit("my_cat();", "calloc 2");
			}
			strlcat(str, buf, str_size + 1);
		}
	}
	if (close(pfd) == -1)
	{
		err_exit("my_cat();", "close(pfd)");
	}
	write(STDOUT_FILENO, str, str_size + 1);
	free(str);
	exit(EXIT_SUCCESS);
}

int	main (void)
{
	int				pfd;
	pid_t			pid;
	int				status = 0;
	char			*line = NULL;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			break ;
		}
		if (strlen(line))
		{
			add_history(line);
		}
		if (strcmp(line, "<<") == 0)
		{
			pfd = here_document();
			if ((pid = fork()) < 0)
			{
				err_exit("main()", "fork();");
			}
			else if (pid == 0)
			{
				my_cat(pfd);
			}
			else
			{
				if (wait(NULL) == -1)
				{
					err_exit("main();", "wait(NULL)");
				}
			}
		}
		free(line);
	}
	system("leaks -q a.out");
	exit(status);
}
