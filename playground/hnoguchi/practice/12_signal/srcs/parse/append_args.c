/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:47:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_last_token(t_token **rest, t_token *token)
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

void	append_args(t_token **args, t_token *add_token)
{
	t_token	*head_p;

	head_p = *args;
	if (add_token == NULL)
	{
		fatal_error("token_dup");
	}
	if (*args == NULL)
	{
		*args = add_token;
		return ;
	}
	list_last_token(args, *args);
	(*args)->next = add_token;
	*args = head_p;
}
