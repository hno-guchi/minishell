/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_append_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:34:18 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_append_output(t_node *node, t_token **rest, t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			fatal_error("parse : token->word == NULL");
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
	}
	else
	{
		fatal_error("parse : token->next->kind != TK_WORD;");
	}
	*rest = token;
}

static void	try_append_input(t_node *node, t_token **rest, t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			fatal_error("parse : token->word == NULL");
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
	}
	else
	{
		fatal_error("parse : token->next->kind != TK_WORD;");
	}
	*rest = token;
}

static void	try_append_append_output(t_node *node, t_token **rest,
		t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			fatal_error("parse : token->word == NULL");
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
	}
	else
	{
		fatal_error("parse : token->next->kind != TK_WORD;");
	}
	*rest = token;
}

static void	try_append_here_document(t_node *node, t_token **rest,
		t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			fatal_error("parse : token->word == NULL");
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
	}
	else
	{
		fatal_error("parse : token->next->kind != TK_WORD;");
	}
	*rest = token;
}

void	try_append_redirect(t_node *node, t_token **rest, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0)
	{
		try_append_output(node, rest, token);
	}
	else if (ft_strcmp(token->word, "<") == 0)
	{
		try_append_input(node, rest, token);
	}
	else if (ft_strcmp(token->word, ">>") == 0)
	{
		try_append_append_output(node, rest, token);
	}
	else if (ft_strcmp(token->word, "<<") == 0)
	{
		try_append_here_document(node, rest, token);
	}
}
