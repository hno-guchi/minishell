/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:49:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

void	list_add_back(t_node **redir, t_token *add_token, t_node_kind kind)
{
	t_node	*head_p;

	head_p = NULL;
	if (!is_kind_node(*redir, kind))
	{
		head_p = *redir;
		list_last_node(redir, *redir);
		(*redir)->next = new_node(kind);
		if ((*redir)->next == NULL)
		{
			fatal_error("new_node");
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
}
