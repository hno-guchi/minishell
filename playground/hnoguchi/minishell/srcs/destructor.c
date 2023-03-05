/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:17 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 09:59:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	frees_argv(char **argv)
{
	while (*argv != NULL)
	{
		free(*argv);
		argv++;
	}
}

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
		if (token->word != NULL)
		{
			free(token->word);
		}
		next_token = token->next;
		free(token);
		token = next_token;
	}
	free(token);
}

static void	list_frees_redirects(t_node *list)
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

void	list_frees_command(t_node *list)
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
		list_frees_redirects(list->redirects);
		next_node = list->next;
		free(list);
		list = next_node;
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
		next_node = node->next;
		free(node);
		node = next_node;
	}
}
