/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/10 19:35:13 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "redirect.h"

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

int	interpret(t_token *token)
{
	extern char		**environ;
	char			**argv;
	char			*path;
	pid_t			pid;
	int				wstatus;

	if (strchr(token->word, '/') == NULL)
	{
		path = search_path(token->word);
		if (path == NULL)
		{
			error_message(path, "command not found", 127);
		}
	}
	else
	{
		path = strdup(token->word);
		if (path == NULL)
		{
			error_message(path, "command not found", 127);
		}
	}
	argv = create_argv(path, token);
	// printf("create_argv();-------\n");
	// int	i = 0;
	// while (argv[i] != NULL)
	// {
	// 	printf("argv[%d] == [%s]\n", i, argv[i]);
	// 	i++;
	// }
	pid = fork();
	if (pid < 0)
	{
		fatal_error("fork");
	}
	else if (pid == 0)
	{
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		frees_argv(argv);
		free(argv);
		return (WEXITSTATUS(wstatus));
	}
	return (258);
}
