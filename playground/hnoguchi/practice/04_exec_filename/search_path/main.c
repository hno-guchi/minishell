/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 12:02:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "search_path.h"

int	main(int argc, char **argv)
{
	char	*my_argv[] = {"./search_path", "echo", "hello", "world", NULL};

	(void)argv;
	if (argc != 2)
	{
		error("Not argument...");
	}
	// interpret(argv);
	interpret(my_argv);
	// system("leaks -q expand");
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
	token = expand(token);
	my_argv = create_argv(token);
	execve("/bin/echo", my_argv, environ);
	exit (0);	
}
*/
