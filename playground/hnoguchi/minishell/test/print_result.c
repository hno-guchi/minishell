/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 10:33:09 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_result_token(t_token *token, const char *message)
{
	printf("%s\n", message);
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
	printf("\n");
}

void	print_result_redirects(t_node *list, const char *message)
{
	printf("%s\n", message);
	while (list != NULL)
	{
		if (list->kind == NODE_REDIR_OUT)
		{
			printf(GREEN"NODE_REDIR_OUT"END); printf("\n");
			print_result_token(list->args, "[node->redirects->args]"); // printf("\n");
		}
		else if (list->kind == NODE_REDIR_IN)
		{
			printf(GREEN"NODE_REDIR_IN"END); printf("\n");
			print_result_token(list->args, "[node->redirects->args]"); // printf("\n");

		}
		list = list->next;
	}
}

void	print_result_parse(t_node *node, char *message)
{
	printf("---------------------------------\n");
	printf("%s\n", message);
	while (node != NULL)
	{
		if (node->kind == NODE_SIMPLE_CMD)
		{
			printf(GREEN"NODE_SIMPLE_CMD"END); printf("\n");
			print_result_token(node->args, "[node->args]"); // printf("\n");
			print_result_redirects(node->redirects, "[node->redirects]"); // printf("\n");
		}
		node = node->next;
	}
}

void	print_result_expand(t_node *node, char *message)
{
	printf("---------------------------------\n");
	printf("%s\n", message);
	while (node != NULL)
	{
		if (node->kind == NODE_SIMPLE_CMD)
		{
			printf(GREEN"NODE_SIMPLE_CMD"END); printf("\n");
			print_result_token(node->args, "[node->args]"); // printf("\n");
			print_result_redirects(node->redirects, "[node->redirects]"); // printf("\n");
		}
		node = node->next;
	}
}

void	print_result_redirect(t_node *node)
{
	dprintf(STDERR_FILENO, "node->input_fd          : [%d]\n", node->input_fd);
	dprintf(STDERR_FILENO, "node->output_fd         : [%d]\n", node->output_fd);
}
