/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_append_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/23 14:28:54 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*try_append(t_node *node, t_node_kind node_kind,
		t_redir_kind redir_kind, t_token *token)
{
	if (token->next->kind != TK_WORD)
	{
		parse_error(&token, token->next);
	}
	else if (token->next->word == NULL)
	{
		parse_error(&token, token);
	}
	else
	{
		token = token->next;
		append_redirects(&node->redirects,
			token_dup(redir_kind, token), node_kind);
	}
	return (token);
}

static t_token	*try_append_here_document(t_node *node, t_node_kind node_kind,
		t_token *token)
{
	if (token->next->kind != TK_WORD)
	{
		parse_error(&token, token->next);
	}
	else if (token->next->word == NULL)
	{
		parse_error(&token, token);
	}
	else
	{
		token = token->next;
		if (!is_quote(token->word))
		{
			append_redirects(&node->redirects,
				token_dup(REDIR_HERE_DOC, token), node_kind);
		}
		else
		{
			append_redirects(&node->redirects,
				token_dup(REDIR_HERE_DOC_NOT_EXPAND, token), node_kind);
		}
	}
	return (token);
}

void	try_append_redirect(t_node *node, t_token **rest, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0)
	{
		*rest = try_append(node, NODE_REDIR_OUT, REDIR_OUT, token);
	}
	else if (ft_strcmp(token->word, "<") == 0)
	{
		*rest = try_append(node, NODE_REDIR_IN, REDIR_IN, token);
	}
	else if (ft_strcmp(token->word, ">>") == 0)
	{
		*rest = try_append(node, NODE_REDIR_OUT, REDIR_APPEND_OUT, token);
	}
	else if (ft_strcmp(token->word, "<<") == 0)
	{
		*rest = try_append_here_document(node, NODE_REDIR_IN, token);
	}
}
