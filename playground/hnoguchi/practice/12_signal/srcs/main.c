/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/15 12:42:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell = {};

void	execute_command(char *line)
{
	t_token	*token;
	t_node	*node;

	token = NULL;
	node = NULL;
	token = tokenize(line);
	if (token->kind == TK_EOF)
	{
		// dprintf(STDERR_FILENO, "token->kind == EOF\n");
		;
	}
	else if (g_minishell.syntax_error == true)
	{
		g_minishell.last_status = ERROR_TOKENIZE;
	}
	else
	{
		node = parse(token);
		node = expand(node);
		if (open_redir_file(node) < 0)
		{
			g_minishell.last_status = ERROR_OPEN_REDIR;
		}
		else
		{
			g_minishell.last_status = interpret(node);
			// dprintf(STDERR_FILENO, "[1] : interpret\n");
			// dprintf(STDERR_FILENO, "last_status : [%d]\n", g_minishell.last_status);
		}
		closes_redirect_file(node);
		// dprintf(STDERR_FILENO, "[2] ; close_redirect_file\n");
		list_frees_node(node);
		// dprintf(STDERR_FILENO, "[3] ; list_frees_node\n");
	}
	list_frees_token(token);
	// dprintf(STDERR_FILENO, "[4] ; list_frees_token\n");
}

static bool	is_break(char *line)
{
	if (line != NULL)
	{
		return (false);
	}
	if (RL_ISSTATE(RL_STATE_EOF))
	{
		return (true);
	}
	else
	{
		g_minishell.last_status = 1;
		return (true);
	}
	return (false);
}

int	main(void)
{
	char	*line;

	line = NULL;
	initialize_signals();
	g_minishell.last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (is_break(line))
		{
			break ;
		}
		if (ft_strlen(line))
		{
			add_history(line);
		}
		execute_command(line);
		free(line);
		set_signals_receiver();
	}
	if (RL_ISSTATE(RL_STATE_EOF))
	{
		ft_putstr_fd("logout\n", STDERR_FILENO);
	}
	exit (g_minishell.last_status);
}

/*
void	execute_command(char *line)
{
	t_token	*token;
	t_node	*node;

	token = NULL;
	node = NULL;
	// printf("line == [%s]\n", line);
	token = tokenize(line);
	// printf("---------------------------------\n");
	// print_result_token(token, "Result tokenize();");
	if (token->kind == TK_EOF)
		;
	else if (g_minishell.syntax_error == true)
	{
		g_minishell.last_status = ERROR_TOKENIZE;
	}
	else
	{
		node = parse(token);
		// print_result_parse(node, "Result parse();");
		node = expand(node);
		// print_result_expand(node, "Result expand();  ");
		if (open_redir_file(node) < 0)
		{
			exit (ERROR_OPEN_REDIR);
		}
		// print_result_redirect(node);
		g_minishell.last_status = interpret(node);
		closes_redirect_file(node);
		list_frees_node(node);
	}
	list_frees_token(token);
}
*/
