/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/27 11:34:50 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_node *node)
{
	int		status;

	status = 0;
	redirect_file(node->command);
	if (ft_strcmp(node->command->args->word, "echo") == 0)
		status = builtin_echo(node);
	else if (ft_strcmp(node->command->args->word, "cd") == 0)
		status = builtin_cd(node);
	else if (ft_strcmp(node->command->args->word, "pwd") == 0)
		status = builtin_pwd(node);
	else if (ft_strcmp(node->command->args->word, "export") == 0)
		status = builtin_export(node);
	else if (ft_strcmp(node->command->args->word, "unset") == 0)
		status = builtin_unset(node);
	else if (ft_strcmp(node->command->args->word, "env") == 0)
		status = builtin_env();
	else if (ft_strcmp(node->command->args->word, "exit") == 0)
		status = builtin_exit(node);
	reset_redirect_command(node->command);
	return (status);
}
