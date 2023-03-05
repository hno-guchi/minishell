/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:45:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/09 17:55:08 by hnoguchi         ###   ########.fr       */
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
	node->target_fd = STDOUT_FILENO;
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

/*
static void	list_last_redirects(t_redirect **rest, t_redirect *redirects)      
{
	if (redirects == NULL)
	{
		return ;
	}
	while (redirects->next != NULL)
	{
		redirects = redirects->next;
	}
	*rest = redirects;
}

static t_redirect	*new_redirects_node(char *file_name)
{
	t_redirect	*new_node;
	char		*dup_name;

	if (file_name == NULL)
		{
		return (NULL);
	}
	new_node = calloc(1, sizeof(t_redirect));
	if (new_node == NULL)
	{
		fatal_error("new_redirects_node: calloc();");
	}
	dup_name = strdup(file_name);
	if (dup_name == NULL)
	{
		fatal_error("node_dup: strdup();");
	}
	new_node->file_name = dup_name;
	return (new_node);
}
*/

static void	append_redirects(t_node **redir, t_token *add_token, t_node_kind kind)
{
	t_node	*head_p;

	head_p = *redir;
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
		append_args(&(*redir)->args, new_token(TK_EOF, NULL));
		return ;
	}
	list_last_node(redir, *redir);
	(*redir)->next = new_node(kind);
	if ((*redir)->next == NULL)
	{
		fatal_error("append_redirects : new_node(kind);");
	}
	*redir = (*redir)->next;
	(*redir)->args = add_token;
	append_args(&(*redir)->args, new_token(TK_EOF, NULL));
	*redir = head_p;
}

/*
 * EBNF
 * <program>                = <simple_command>
 * <simple_command>         = <simple_command_element>+
 * <simple_command_element> = <redirect>
 *                          | <word>
 *
 * <redirect> = <redirect_out>
 *
 * <redirect_out> = ">" <word>
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
					token = token->next;
					if (token->word == NULL)
					{
						fatal_error("parse : token->word == NULL");
					}
					append_redirects(&node->redirects, token_dup(token), NODE_REDIR_OUT);
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
	append_args(&node->args, new_token(TK_EOF, NULL));
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

