/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/22 13:44:54 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_dup(t_redir_kind redir_kind, t_token *source)
{
	char	*word;

	if (source == NULL)
	{
		return (NULL);
	}
	word = ft_strdup(source->word);
	if (word == NULL)
	{
		fatal_error("strdup");
	}
	return (new_token(source->kind, redir_kind, word));
}

/*
 * EBNF
 * <program>                = <simple_command>
 * <pipeline>               = <simple_command> ('|' <pipeline>)
 * <simple_command>         = <simple_command_element>+
 * <simple_command_element> = <word>
 *                          | <redirection>
 *
 * <redirection> = <redirect_out>
 *               | <redirect_in>
 *               | <redirect_append_out>
 *               | <redirect_here_document>
 *
 * <redirect_out> = ">" <word>
 * <redirect_in>  = "<" <word>
 * <redirect_append_out> = ">>" <word>
 * <redirect_heredoc> = "<<" <word>
 */
t_node	*parse_simple_command(t_token **rest, t_token *token)
{
	t_node	*node;

	node = new_node(NODE_SIMPLE_CMD);
	if (node == NULL)
		fatal_error("new_node");
	while (token != NULL && !at_eof(token->kind))
	{
		if (token->kind == TK_WORD)
		{
			append_args(&node->args, token_dup(REDIR_NOT, token));
		}
		else if (token->kind == TK_REDIRECTION)
		{
			try_append_redirect(node, &token, token);
		}
		else if (token->kind == TK_CONTROL)
			break ;
		else
			parse_error(&token, token);
		if (g_minishell.syntax_error == true)
			break ;
		token = token->next;
	}
	*rest = token;
	return (node);
}

static t_node	*try_create_new_node(t_token *token)
{
	t_node	*node;

	node = NULL;
	if (token->kind != TK_CONTROL)
		fatal_error("try_create_new_node");
	if (ft_strcmp(token->word, "|") == 0)
	{
		if (token->next->kind == TK_WORD || token->next->kind == TK_REDIRECTION)
		{
			node = new_node(NODE_PIPELINE);
			if (node == NULL)
			{
				fatal_error("new_node");
			}
			return (node);
		}
		else
			parse_error(&token, token);
	}
	else
	{
		parse_error(&token, token);
	}
	return (NULL);
}

t_node	*parse(t_token *token)
{
	t_node	*node;
	t_node	*head_p;

	if (token->kind == TK_CONTROL)
	{
		parse_error(&token, token);
		return (NULL);
	}
	node = new_node(NODE_PIPELINE);
	head_p = node;
	if (node == NULL)
		fatal_error("new_node");
	while (token != NULL && !at_eof(token->kind))
	{
		node->command = parse_simple_command(&token, token);
		if (token->kind == TK_CONTROL)
		{
			node->next = try_create_new_node(token);
			node = node->next;
		}
		if (g_minishell.syntax_error == true)
			break ;
		token = token->next;
	}
	return (head_p);
}
