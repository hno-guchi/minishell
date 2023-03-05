/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:31:38 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/02 16:43:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	append_token_recursive(t_token **tokens, t_token *new_token)
{
	if (*tokens == NULL)
	{
		tokens = new_token;
		return ;
	}
	append_token(&(*tokens)->next, new_token);
}

void	list_free_token_recursive(t_token *token)
{
	if (token == NULL)
	{
		return ;
	}
	list_free_token_recursive(token->next);
	free(token->word);
	free(token);
}

void	list_free_node_recursive(t_node *node)
{
	if (node == NULL)
	{
		return ;
	}
	list_free_node_recursive(node->next);
	list_free_token_recursive(node->args);
	free(node);
}
