/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/22 17:06:19 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_frees_token(t_token *token)
{
	t_token	*next_token;

	next_token = NULL;
	if (token == NULL)
	{
		return ;
	}
	while (token != NULL)
	{
		free(token->word);
		next_token = token->next;
		free(token);
		token = next_token;
	}
	free(token);
}

void	list_frees_redirects(t_node *list)
{
	t_node	*next_node;

	next_node = NULL;
	if (list == NULL)
	{
		return ;
	}
	while (list != NULL)
	{
		list_frees_token(list->args);
		next_node = list->next;
		free(list);
		list = next_node;
	}
}

void	list_frees_command(t_node *node)
{
	t_node	*next_node;

	next_node = NULL;
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		list_frees_token(node->args);
		list_frees_redirects(node->redirects);
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

void	list_frees_node(t_node *node)
{
	t_node	*next_node;

	next_node = NULL;
	if (node == NULL)
	{
		return ;
	}
	while (node != NULL)
	{
		list_frees_command(node->command);
		// list_frees_token(node->args);
		// list_frees_redirects(node->redirects);
		next_node = node->next;
		free(node);
		node = next_node;
	}
}
