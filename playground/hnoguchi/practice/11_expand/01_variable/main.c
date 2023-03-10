/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 19:39:01 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_minishell(char **test_case)
{
	int		status;
	t_token *token;
	t_node	*node;

	if (*test_case == NULL)
	{
		return (0);
	}
	dprintf(STDOUT_FILENO, "\n~$ %s\n", *test_case);
	dprintf(STDOUT_FILENO, "==============================================\n");

	status = 0;
	token = tokenize(*test_case);

	print_result_token(token, "Result tokenize();");

	node = parse(token);
	print_result_parse(node, "Result parse();");

	node = expand(node);
	print_result_expand(node, "Result expand();");

	// redirect(node);
	if (open_redir_file(node) < 0)
	{
		return (ERROR_OPEN_REDIR);
	}
	// print_result_redirects(node, "Result print_result_redirects();");
	// execve("/bin/echo", argv, environ);
	// dprintf(STDOUT_FILENO, "node->command->redirects->args->word : [%s]\n", node->command->redirects->args->word);
	status = interpret(node);
	dprintf(STDOUT_FILENO, "==============================================\n");
	closes_redirect_file(node);
	// dprintf(STDOUT_FILENO, "STDIN_FILENO : [%d]\n", STDIN_FILENO);
	// dprintf(STDOUT_FILENO, "STDOUT_FILENO : [%d]\n", STDOUT_FILENO);
	// dprintf(STDERR_FILENO, "STDERR_FILENO : [%d]\n", STDERR_FILENO);
	// dprintf(STDOUT_FILENO, "HELLO, WORLD\n");

	list_frees_node(node);
	list_frees_token(token);

	test_case++;
	test_minishell(test_case);
	return (status);
}

int	main(void)
{
	int		status;
	char	*test_case[] = {
		"echo $USER",
		"echo $NOT",
		"echo $USER$PATH$NOT",
		"echo $USER   $PATH     $NOT",
		"echo \"$USER   $PATH     $NOT\"",
		"echo \"$USER   $PATH     a$NOT\"",
		"echo \"$NOT\"",
		NULL,
	};

	status = test_minishell(test_case);
	// system("leaks -q expand_variable");
	// while(1)
	// 	;
	exit (status);	
}
