/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/21 20:29:07 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node *node)
{
	int		status;

	status = 0;
	redirect_file(node->command);
	if (ft_strcmp(node->command->args->word, "echo") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "cd") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "pwd") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "export") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "unset") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "env") == 0)
		;
	else if (ft_strcmp(node->command->args->word, "exit") == 0)
		;
	reset_redirect_command(node->command);
	return (status);
}
