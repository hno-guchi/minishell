/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:18 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:45:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
	{
		fatal_error("ft_calloc");
	}
	node->kind = kind;
	node->input_fd = STDIN_FILENO;
	node->output_fd = STDOUT_FILENO;
	return (node);
}
