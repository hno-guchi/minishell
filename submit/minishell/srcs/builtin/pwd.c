/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:25:06 by asasada           #+#    #+#             */
/*   Updated: 2023/03/26 22:46:20 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arglen(t_token *args)
{
	int	argc;

	argc = 0;
	while (args != NULL)
	{
		argc++;
		args = args->next;
	}
	return (argc);
}

void	remove_private_prefix(char *path)
{
	size_t	prefix_len;
	size_t	path_len;

	prefix_len = ft_strlen("/private");
	path_len = ft_strlen(path);
	if (ft_strncmp(path, "/private", prefix_len) == 0)
	{
		ft_memmove(path, path + prefix_len, path_len - prefix_len + 1);
	}
}

int	builtin_pwd(t_node *node)
{
	char	cwd[PATH_MAX];

	(void)node;
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		builtin_error("pwd", NULL, "getcwd");
		return (1);
	}
	remove_private_prefix(cwd);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

// int	builtin_pwd(t_node *node)
// {
// 	char	*pwd;
// 	char	cwd[PATH_MAX];

// 	(void)node;
// 	pwd = get_map_value("PWD");
// 	if (pwd == NULL || !inode_is_equal(pwd, "."))
// 	{
// 		if (getcwd(cwd, PATH_MAX) == NULL)
// 		{
// 			builtin_error("pwd", NULL, "getcwd");
// 			free(pwd);
// 			return (1);
// 		}
// 		ft_putendl_fd(cwd, STDOUT_FILENO);
// 	}
// 	else
// 	{
// 		ft_putendl_fd(pwd, STDOUT_FILENO);
// 	}
// 	if (pwd != NULL)
// 		free(pwd);
// 	return (0);
// }
