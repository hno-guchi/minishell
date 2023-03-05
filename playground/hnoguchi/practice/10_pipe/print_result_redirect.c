/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/24 13:27:38 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_result_redirects(t_node *list, const char *message)
{
	if (list == NULL)
	{
		dprintf(STDERR_FILENO, "print_result_redirects(); list is (NULL);\n");
		return ;
	}
	dprintf(STDERR_FILENO, "%s\n", message);
	while (list != NULL)
	{
		if (list->kind == NODE_REDIR_OUT)
		{
			printf(GREEN"NODE_REDIR_OUT"END); printf("\n");
			print_token(list->args, "[node->command->redirects->args]"); // printf("\n");
		}
		else if (list->kind == NODE_REDIR_IN)
		{
			printf(GREEN"NODE_REDIR_IN"END); printf("\n");
			print_token(list->args, "[node->command->redirects->args]"); // printf("\n");

		}
		list = list->next;
	}
}

void	print_result_redirect(t_node *node)
{
	if (node == NULL)
	{
		dprintf(STDERR_FILENO, "print_result_redirect(); node is (NULL);\n");
		return ;
	}
	dprintf(STDERR_FILENO, " input_fd         : [%d]\n", node->input_fd);
	dprintf(STDERR_FILENO, "output_fd         : [%d]\n", node->output_fd);
}

// redirect.c
void	do_print_result_redir(t_token *token)
{
	if (token == NULL)
	{
		dprintf(STDERR_FILENO, "do_print_result_redir(); token is (NULL);\n");
		return ;
	}
	if (token->kind == TK_OPERATOR)
	{
		dprintf(STDERR_FILENO, "\ntoken->word           : [%s]\n\n", token->word);
	}
	if (token->kind == TK_WORD)
	{
		dprintf(STDERR_FILENO, "token->word            : [%s]\n", token->word);
		dprintf(STDERR_FILENO, "token->file_fd         : [%d]\n", token->file_fd);
		dprintf(STDERR_FILENO, "token->stashed_file_fd : [%d]\n", token->stashed_file_fd);
	}
}

void	print_result_open_redir(t_token *token, char *message)
{
	if (token == NULL)
	{
		dprintf(STDERR_FILENO, "print_result_open_redir(); token is (NULL);\n");
		return ;
	}
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, GREEN"%s"END, message);
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, "----------------------------------------\n");
	while (token != NULL)
	{
		do_print_result_redir(token);
		token = token->next;
	}
	dprintf(STDERR_FILENO, "----------------------------------------\n");
}

void	print_result_close_redir(int *target, t_token *token, char *message)
{
	if (token == NULL)
	{
		dprintf(STDERR_FILENO, "print_result_close_redir(); token is (NULL);\n");
		return ;
	}
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, RED"%s"END, message);
	dprintf(STDERR_FILENO, "\n");
	dprintf(STDERR_FILENO, "----------------------------------------\n");
	dprintf(STDERR_FILENO, "target_fd              : [%d]\n\n", *target);
	do_print_result_redir(token);
	dprintf(STDERR_FILENO, "----------------------------------------\n");
}
