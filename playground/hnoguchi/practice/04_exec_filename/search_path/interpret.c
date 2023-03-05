/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 11:54:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search_path.h"

/*
char	**create_argv(t_token *token)
{
	char	**argv;
	size_t	i;
	size_t	size;
	t_token	*head_p;

	i = 0;
	size = 0;
	head_p = token;
	while (token->kind != TK_EOF)
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
	while (token->kind != TK_EOF)
	{
		argv[i] = token->word;
		token = token->next;
		i += 1;
	}
	token = head_p;
	return (argv);
}
*/

int	interpret(char **argv)
{
	extern char		**environ;
	const char		*path;
	pid_t			pid;
	int				wstatus;

	if (strchr(argv[1], '/') == NULL)
	{
		path = search_path(argv[1]);
		if (path == NULL)
		{
			error_message(path, "command not found", 127);
		}
	}
	else
	{
		path = argv[1];
	}
	pid = fork();
	if (pid < 0)
	{
		fatal_error("fork");
	}
	else if (pid == 0)
	{
		execve(path, &argv[1], environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	exit(1);
}
