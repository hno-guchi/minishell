/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_append_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 14:31:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_append_output(t_node *node, t_token **rest, t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			parse_error(&token, token);
			*rest = token;
			return ;
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
	}
	else
	{
		parse_error(&token, token->next);
	}
	*rest = token;
}

static void	try_append_input(t_node *node, t_token **rest, t_token *token)
{
	if (token->next->kind == TK_WORD)
	{
		if (token->next->word == NULL)
		{
			parse_error(&token, token);
			*rest = token;
			return ;
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
	}
	else
	{
		parse_error(&token, token->next);
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
			parse_error(&token, token);
			*rest = token;
			return ;
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
	}
	else
	{
		parse_error(&token, token->next);
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
			parse_error(&token, token);
			*rest = token;
			return ;
		}
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
		token = token->next;
		append_redirects(&node->redirects, token_dup(token), NODE_REDIR_IN);
	}
	else
	{
		parse_error(&token, token->next);
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
