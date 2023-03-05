/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/16 18:08:45 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include "tokenize.h"
# include "parse.h"
# include "redirect.h"

void	list_frees_token(t_token *token)
{
	t_token	*next_token;

	next_token = NULL;
	if (token == NULL)
	{
		return ;
	}
	while (token != NULL)
	{
		free(token->word);
		next_token = token->next;
		free(token);
		token = next_token;
	}
	free(token);
}

void	list_frees_redirects(t_node *list)
{
	t_node	*next_node;

	next_node = NULL;
	if (list == NULL)
	{
		return ;
	}
	while (list != NULL)
	{
		list_frees_token(list->args);
		next_node = list->next;
		free(list);
		list = next_node;
	}
}

void	list_frees_node(t_node *node)
{
	t_node	*next_node;

	next_node = NULL;
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		list_frees_token(node->args);
		list_frees_redirects(node->redirects);
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

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
	dprintf(STDERR_FILENO, " input_fd->target         : [%d]\n", node->input_fd.target);
	// dprintf(STDERR_FILENO, " input_fd->stashed_target : [%d]\n", node->input_fd.stashed_target);
	dprintf(STDERR_FILENO, "output_fd->target         : [%d]\n", node->output_fd.target);
	// dprintf(STDERR_FILENO, "output_fd->stashed_target : [%d]\n", node->output_fd.stashed_target);

}

int	main(void)
{
	int		status;
	t_token *token;
	t_node	*node;
	// char	*line = "echo <<FINISH <hello.txt >> f2 >f1 >>fire.txt << EOF";
	// char	*line = "cat << EOF";
	// char	*line = "cat < hello.txt << EOF";
	// char	*line = "cat < hello.txt << EOF < hello.txt";
	// char	*line = "cat <<EOF <hello.txt";
	// char	*line = "cat << EOF << FIN";
	char	*line = "cat < hello.txt << EOF < world.txt";
	// char	*line = "cat < \"hello.txt\" > 'f1' >\"f2\" <'input.txt'";
	// extern char	**environ;
	// char		*argv[] = {"/bin/cat", "hello world!", NULL};

	status = 0;
	token = tokenize(line);

	printf("\n~$ %s\n", line);
	// printf("---------------------------------\n");
	// print_result_token(token, "Result tokenize();");

	node = parse(token);
	// print_result_parse(node, "Result parse();");

	node = expand(node);
	// print_result_expand(node, "Result expand();  ");

	redirect(node);
	// print_result_redirect(node);
	// execve("/bin/echo", argv, environ);
	status = interpret(node->args);
	reset_redirect(node);
	dprintf(STDOUT_FILENO, "HELLO, WORLD\n");

	list_frees_token(token);
	list_frees_node(node);
	system("leaks -q here_document");
	exit (status);	
}
