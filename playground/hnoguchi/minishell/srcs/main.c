/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/14 20:11:52 by hnoguchi         ###   ########.fr       */
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
		;
	else if (g_minishell.syntax_error == true)
		g_minishell.last_status = ERROR_TOKENIZE;
	else
	{
		node = parse(token);
		node = expand(node);
		if (open_redir_file(node) < 0)
			g_minishell.last_status = ERROR_OPEN_REDIR;
		else
			g_minishell.last_status = interpret(node);
		closes_redirect_file(node);
		list_frees_node(node);
	}
	list_frees_token(token);
}

int	main(void)
{
	char	*line;

	line = NULL;
	initialize_signals();
	rl_outstream = stderr;
	g_minishell.syntax_error = false;
	g_minishell.last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
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
	exit (g_minishell.last_status);
}
