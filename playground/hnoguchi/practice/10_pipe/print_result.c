/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 13:26:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main.c
void	print_result_token(t_token *token, const char *message)
{
	if (token == NULL)
	{
		return ;
	}
	dprintf(STDOUT_FILENO, "\n%s\n", message);
	dprintf(STDOUT_FILENO, "---------------------------------\n");
	while (token != NULL)
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
		else if (token->kind == TK_EOF)
		{
			printf("TK_EOF   is [%s]\n", token->word);
		}
		else
		{
			printf("bad is [%s]\n", token->word);
		}
		token = token->next;
	}
	// printf("\n");
}

void	print_token(t_token *token, const char *message)
{
	if (token == NULL)
	{
		return ;
	}
	if (message != NULL)
	{
		dprintf(STDOUT_FILENO, "%s\n", message);
	}
	while (token != NULL)
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
		else if (token->kind == TK_EOF)
		{
			printf("TK_EOF   is [%s]\n", token->word);
		}
		else
		{
			printf("bad is [%s]\n", token->word);
		}
		token = token->next;
	}
}

void	print_result_simple_command(t_node *node, char *message)
{
	dprintf(STDOUT_FILENO, "%s\n", message);
	if (node->kind == NODE_SIMPLE_CMD)
	{
		// printf(GREEN"NODE_SIMPLE_CMD"END); printf("\n");
		print_token(node->args, NULL); // printf("\n");
		print_result_redirects(node->redirects, "[node->command->redirects]"); // printf("\n");
	}
}

static void	print_node(t_node *node, char *message)
{
	if (node == NULL)
	{
		return ;
	}
	if (message != NULL)
	{
		dprintf(STDOUT_FILENO, "%s\n", message);
	}
	/*
	if (node->kind == NODE_PIPELINE)
	{
		dprintf(STDOUT_FILENO, "======== PIPELINE ========\n");
		dprintf(STDOUT_FILENO, "node->pipe_fd[0] is [%d]\n", node->pipe_fd[0]);
		dprintf(STDOUT_FILENO, "node->pipe_fd[1] is [%d]\n", node->pipe_fd[1]);
		print_result_simple_command(node->command, "[node->command->args]");
		dprintf(STDOUT_FILENO, "==========================\n\n");
	}
	*/
}

void	print_result_parse(t_node *node, char *message)
{
	dprintf(STDOUT_FILENO, "\n%s\n", message);
	dprintf(STDOUT_FILENO, "---------------------------------\n");
	while (node != NULL)
	{
		print_node(node, NULL);
		node = node->next;
	}
}

void	print_result_expand(t_node *node, char *message)
{
	printf("%s\n", message);
	printf("---------------------------------\n");
	while (node != NULL)
	{
		print_node(node, NULL);
		node = node->next;
	}
}

// interpret.c
void	print_result_create_argv(char **argv)
{
	int	i;

	i = 0;
	dprintf(STDOUT_FILENO, "create_argv();-------\n");
	while (argv[i] != NULL)
	{
		dprintf(STDOUT_FILENO, "argv[%d] == [%s]\n", i, argv[i]);
		i++;
	}
}
