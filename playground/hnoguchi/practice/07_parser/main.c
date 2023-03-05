/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/08 12:23:04 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include "tokenize.h"
# include "parser.h"

void	list_free_token(t_token *token)
{
	t_token	*next_token;

	next_token = NULL;
	if (token == NULL)
	{
		return ;
	}
	while (token->kind != TK_EOF)
	{
		free(token->word);
		next_token = token->next;
		free(token);
		token = next_token;
	}
	free(token);
}

void	list_free_node(t_node *node)
{
	t_node	*next_node;

	next_node = NULL;
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		list_free_token(node->args);
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

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

void	print_result_token(t_token *token, const char *message)
{
	printf("%s----------\n", message);
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
}

void	print_result_parser(t_node *node, char *message)
{
	printf("\n%s-----------\n", message);
	while (node != NULL)
	{
		if (node->kind == NODE_SIMPLE_COMMAND)
		{
			printf(GREEN"NODE_SIMPLE_COMMAND"END);
			printf("\n");
			print_result_token(node->args, "[node->args]");
			// printf("node->args->word: [%s]\n", node->args->word);
		}
		node = node->next;
	}
}

void	print_result_expand(t_node *node, char *message)
{
	printf("\n%s-----------\n", message);
	while (node != NULL)
	{
		if (node->kind == NODE_SIMPLE_COMMAND)
		{
			printf(GREEN"NODE_SIMPLE_COMMAND"END);
			printf("\n");
			print_result_token(node->args, "[node->args]");
			// printf("node->args->word: [%s]\n", node->args->word);
		}
		node = node->next;
	}
}

// test case
// token = tokenize("echo \"'hello' 'world'\""); // 7_parser
int	main(void)
{
	t_token *token;
	t_node	*node;

	token = tokenize("echo hello > hello.txt"); // 9_redirect_output
	print_result_token(token, "Result tokenize();");

	node = parser(token);
	print_result_parser(node, "Result parser();  ");

	node = expand(node);
	print_result_expand(node, "Result expand();  ");

	list_free_token(token);
	list_free_node(node);
	system("leaks -q parser");
	exit (0);	
}
