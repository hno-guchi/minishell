/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:52:50 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_redirects(t_node **redir, t_token *add_token,
		t_node_kind kind)
{
	if (add_token == NULL)
	{
		fatal_error("token_dup");
	}
	if (*redir == NULL)
	{
		*redir = new_node(kind);
		if (*redir == NULL)
		{
			fatal_error("new_node");
		}
		(*redir)->args = add_token;
		return ;
	}
	else
	{
		list_add_back(redir, add_token, kind);
	}
}
