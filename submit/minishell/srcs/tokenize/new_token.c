/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/18 17:31:01 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_kind kind, t_redir_kind redir_kind, char *word)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		fatal_error("ft_calloc");
	}
	new_token->word = word;
	new_token->kind = kind;
	new_token->redir_kind = redir_kind;
	new_token->file_fd = -1;
	new_token->stashed_file_fd = -1;
	new_token->next = NULL;
	return (new_token);
}
