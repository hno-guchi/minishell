/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 15:04:13 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		status;
	t_token *token;
	t_node	*node;
	// char	*line = "/bin/pwd";
	char	*line = "cat Makefile | grep minishell";
	// char	*line = "cat print_result_pipe.c";
	// char	*line = "cat print_result_pipe.c | grep dprintf";
	// char	*line = "cat print_result_pipe.c | grep dprintf | wc -l";
	// char	*line = "cat print_result_pipe.c | grep dprintf > result.txt";
	// char	*line = "cat print_result_pipe.c | grep dprintf > result.txt";
	// char	*line = "cat < print_result_pipe.c | grep \"pipe\" > result.txt";
	// char	*line = "cat << EOF | grep \"pipe\" > result.txt";

	// char	*line = "cat print_result_pipe.c > result.txt";
	// char	*line = "cat print_result_pipe.c >> result.txt";
	// char	*line = "cat print_result_pipe.c > result.txt > f1 > f2 > f3";

	// char	*line = "cat < print_result_pipe.c > f1";
	// char	*line = "cat << EOF > f1";
	// char	*line = "cat < print_result_pipe.c << EOF < print_result_pipe.c";

	// char	*line = "cat < print_result_pipe.c << EOF < print_result_pipe.c > f1 > f2 > f3";

	status = 0;
	token = tokenize(line);

	dprintf(STDOUT_FILENO, "\n~$ %s\n", line);
	dprintf(STDOUT_FILENO, "---------------------------------\n");
	// print_result_token(token, "Result tokenize();");

	node = parse(token);
	// print_result_parse(node, "Result parse();");

	node = expand(node);
	// print_result_expand(node, "Result expand();");

	// redirect(node);
	if (open_redir_file(node) < 0)
	{
		return (ERROR_OPEN_REDIR);
	}
	// print_result_redirects(node, "Result print_result_redirects();");
	// execve("/bin/echo", argv, environ);
	// dprintf(STDOUT_FILENO, "node->command->redirects->args->word : [%s]\n", node->command->redirects->args->word);
	status = interpret(node);
	closes_redirect_file(node);
	// dprintf(STDOUT_FILENO, "STDIN_FILENO : [%d]\n", STDIN_FILENO);
	// dprintf(STDOUT_FILENO, "STDOUT_FILENO : [%d]\n", STDOUT_FILENO);
	// dprintf(STDERR_FILENO, "STDERR_FILENO : [%d]\n", STDERR_FILENO);
	// dprintf(STDOUT_FILENO, "HELLO, WORLD\n");

	list_frees_node(node);
	list_frees_token(token);
	// system("leaks -q pipeline");
	// while(1)
	// 	;
	exit (status);	
}
