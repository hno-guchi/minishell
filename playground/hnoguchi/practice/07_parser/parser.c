/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:45:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/03 16:25:49 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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

static void	last_token(t_token **rest, t_token *token)
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

static void	append_args(t_token **args, t_token *add_token)
{
	t_token *head_p;

	head_p = *args;
	if (add_token == NULL)
	{
		return ;
	}
	if (*args == NULL)
	{
		*args = add_token;
		return ;
	}
	last_token(args, *args);
	(*args)->next = add_token;
	*args = head_p;
}

/*
 * EBNF
 * <program>                = <simple_command>
 * <simple_command>         = <simple_command_element>+
 * <simple_command_element> = <word>
 *
 */

t_node	*parser(t_token *token)
{
	t_node *node;

	node = new_node(NODE_SIMPLE_COMMAND);
	if (node == NULL)
	{
		fatal_error("parser : new_node();");
	}
	while (token != NULL && !at_eof(token->kind))
	{
		if (token->kind == TK_WORD)
		{
			append_args(&node->args, token_dup(token));
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
