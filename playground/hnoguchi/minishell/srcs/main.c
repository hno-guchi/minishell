/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/15 18:30:46 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell = {};

static void	execute(t_token *token)
{
	t_node	*node;

	node = NULL;
	node = parse(token);
	if (g_minishell.syntax_error == true)
	{
		g_minishell.last_status = ERROR_PARSE;
	}
	else
	{
		node = expand(node);
		if (open_redir_file(node) < 0)
		{
			g_minishell.last_status = ERROR_OPEN_REDIR;
		}
		else
		{
			g_minishell.last_status = interpret(node);
		}
		closes_redirect_file(node);
	}
	list_frees_node(node);
}

static void	execute_command(char *line)
{
	t_token	*token;

	token = NULL;
	token = tokenize(line);
	if (token->kind == TK_EOF)
		;
	else if (g_minishell.syntax_error == true)
	{
		g_minishell.last_status = ERROR_TOKENIZE;
	}
	else
	{
		execute(token);
	}
	list_frees_token(token);
}

static bool	is_break(char *line)
{
	if (line != NULL)
	{
		return (false);
	}
	else if (RL_ISSTATE(RL_STATE_EOF))
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
	rl_outstream = stderr;
	g_minishell.syntax_error = false;
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
		ft_putstr_fd("logout\n", STDERR_FILENO);
	exit (g_minishell.last_status);
}
