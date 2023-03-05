/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:45:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/16 11:35:12 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "tokenize.h"

static t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (node == NULL)
	{
		fatal_error("node calloc");
	}
	node->kind = kind;
	node->input_fd.target = STDIN_FILENO;
	// node->input_fd.stashed_target = 0;
	node->output_fd.target = STDOUT_FILENO;
	// node->output_fd.stashed_target = 0;
	return (node);
}

static bool	at_eof(t_token_kind kind)
{
	return (kind == TK_EOF);
}

static t_token	*token_dup(t_token *source)
{
	char	*word;

	if (source == NULL)
	{
		return (NULL);
	}
	word = strdup(source->word);
	if (word == NULL)
	{
		fatal_error("token_dup: strdup();");
	}
	return (new_token(source->kind, word));
}

static void	list_last(t_token **rest, t_token *token)
{
	if (token == NULL)
	{
		return ;
	}
	while (token->next != NULL)
	{
		token = token->next;
	}
	*rest = token;
}

static void	list_last_node(t_node **rest, t_node *node)
{
	if (node == NULL)
	{
		return ;
	}
	while (node->next != NULL)
	{
		node = node->next;
	}
	*rest = node;
}

static void	append_args(t_token **args, t_token *add_token)
{
	t_token *head_p;

	head_p = *args;
	if (add_token == NULL)
	{
		fatal_error("append_args: token_dup();");
	}
	if (*args == NULL)
	{
		*args = add_token;
		return ;
	}
	list_last(args, *args);
	(*args)->next = add_token;
	*args = head_p;
}

static bool	is_kind_node(t_node *node, t_node_kind kind)
{
	if (node == NULL)
	{
		return (false);
	}
	while (node != NULL)
	{
		if (node->kind == kind)
		{
			return (true);
		}
		node = node->next;
	}
	return (false);
}

static void	move_kind_node(t_node **rest, t_node *node, t_node_kind kind)
{
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		if (node->kind == kind)
		{
			*rest = node;
			return ;
		}
		node = node->next;
	}
	return ;
}

static void	append_redirects(t_node **redir, t_token *add_token, t_node_kind kind)
{
	t_node	*head_p;

	head_p = NULL;
	if (add_token == NULL)
	{
		fatal_error("append_redirects: token_dup();");
	}
	if (*redir == NULL)
	{
		*redir = new_node(kind);
		if (*redir == NULL)
		{
			fatal_error("append_redirects : new_node(kind);");
		}
		(*redir)->args = add_token;
		return ;
	}
	else if (!is_kind_node(*redir, kind))
	{
		head_p = *redir;
		list_last_node(redir, *redir);
		(*redir)->next = new_node(kind);
		if ((*redir)->next == NULL)
		{
			fatal_error("append_redirects : new_node(kind);");
		}
		*redir = (*redir)->next;
		append_args(&(*redir)->args, add_token);
	}
	else
	{
		head_p = *redir;
		move_kind_node(redir, *redir, kind);
		append_args(&(*redir)->args, add_token);
	}
	*redir = head_p;
	return ;
}

/*
 * EBNF
 * <program>                = <simple_command>
 * <simple_command>         = <simple_command_element>+
 * <simple_command_element> = <redirect>
 *                          | <word>
 *
 * <redirect> = <redirect_out>
 *            | <redirect_in>
 *            | <redirect_append_out>
 *
 * <redirect_out> = ">" <word>
 * <redirect_in>  = "<" <word>
 * <redirect_append_out> = ">>" <word>
 * <redirect_heredoc> = "<<" <word>
 */
t_node	*parse(t_token *token)
{
	t_node *node;

	node = new_node(NODE_SIMPLE_CMD);
	if (node == NULL)
	{
		fatal_error("parse : new_node(NODE_SIMPLE_CMD);");
	}
	while (token != NULL && !at_eof(token->kind))
	{
		if (token->kind == TK_WORD)
		{
			append_args(&node->args, token_dup(token));
		}
		else if (token->kind == TK_OPERATOR)
		{
			if (strcmp(token->word, ">") == 0)
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
					fatal_error("parse : token->next->kind != TK_WORD");
				}
			}
			else if (strcmp(token->word, "<") == 0)
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
					fatal_error("parse : token->next->kind != TK_WORD");
				}
			}
			else if (strcmp(token->word, ">>") == 0)
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
					fatal_error("parse : token->next->kind != TK_WORD");
				}
			}
			else if (strcmp(token->word, "<<") == 0)
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
					fatal_error("parse : token->next->kind != TK_WORD");
				}
			}
		}
		else
		{
			todo("Implement parser"); 
		}
		token = token->next;
	}
	return (node);
}

/*
static void	append_node(void **list, void *add_node)
{
	t_redirect	*head_p;

	head_p = *list;
	if (add_node == NULL)
	{
		fatal_error("append_node: add_node;");
	}
	if (*list == NULL)
	{
		*list = add_node;
		return ;
	}
	list_last_node(list, *list);
	(*list)->next = add_node;
	*list = head_p;
}
*/

