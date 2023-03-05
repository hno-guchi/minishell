/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/03 11:38:27 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token	*tokenize(char *line)
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
			current_token->next = new_token_type_operator(&line, line);
			current_token = current_token->next;
		}
		else if (is_word(*line))
		{
			current_token->next = new_token_type_word(&line, line);
			current_token = current_token->next;
		}
		else
		{
			fatal_error("tokenize");
		}
	}
	current_token->next = new_token(TK_EOF, NULL);
	return (head.next);
}
