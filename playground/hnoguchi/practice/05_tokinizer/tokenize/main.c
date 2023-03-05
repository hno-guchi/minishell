/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/09 14:30:10 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include "tokenize.h"

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
		error("calloc");
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

int	main(int argc, char **argv)
{
	t_token *token;

	(void)argv;
	if (argc != 2)
	{
		error("Not argument...");
	}
	// token = tokenize("echo hello > test.txt");
	// token = tokenize("echo \"a b$HOME\"cdef$HOME' $HOME'\" \"'$HOME%%'\"#+=&$HOME\"");
	// token = tokenize("echo \"a$HOME\"");
	token = tokenize("echo \"$HOME\"b");

	// printf("SUCCESS tokenize\n");
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			printf(GREEN"WORD"END);
			printf("     is [%s]\n", token->word);
		}
		else if (token->kind == TK_OPERATOR)
		{
			printf("OPERATOR is [%s]\n", token->word);
		}
		else
		{
			printf("bad is [%s]\n", token->word);
		}
		token = token->next;
	}
	exit (0);	
}

/*
int	main(int argc, char **argv)
{
	char	**my_argv;
	extern char	**environ;
	t_token *token;

	(void)argv;
	if (argc != 2)
	{
		error("Not argument...");
	}
	token = tokenize("echo hello\tworld");
	my_argv = create_argv(token);
	execve("/bin/echo", my_argv, environ);
	exit (0);	
}
*/
