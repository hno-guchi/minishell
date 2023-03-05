/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 16:45:53 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line, int last_status)
{
	t_token	head;
	t_token	*current_token;

	head.next = NULL;
	current_token = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
		{
			continue ;
		}
		else if (is_meta_character(*line))
		{
			current_token->next = new_token_type_operator(last_status, &line, line);
			current_token = current_token->next;
		}
		else if (is_word(*line))
		{
			current_token->next = new_token_type_word(last_status, &line, line);
			current_token = current_token->next;
		}
		else
		{
			fatal_error("tokenize");
		}
	}
	current_token->next = new_token(TK_EOF, NULL, last_status);
	return (head.next);
}
