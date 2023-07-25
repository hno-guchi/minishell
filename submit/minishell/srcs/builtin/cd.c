/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:15:54 by asasada           #+#    #+#             */
/*   Updated: 2023/03/19 17:15:54 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_new_dir(t_token *args, int argc, bool *print_newdir)
{
	char	*newpwd;
	char	*path;

	if (args != NULL)
		path = args->word;
	if (argc == 1 || ft_strcmp(path, "~") == 0)
	{
		newpwd = get_map_value("HOME");
		if (newpwd == NULL)
			builtin_error("cd", NULL, "HOME not set");
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		*print_newdir = true;
		newpwd = get_map_value("OLDPWD");
		if (newpwd == NULL)
			builtin_error("cd", NULL, "OLDPWD not set");
	}
	else
	{
		newpwd = ft_strdup(path);
		if (newpwd == NULL)
			fatal_error("ft_strdup");
	}
	return (newpwd);
}

static char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (cwd == NULL)
	{
		fatal_error("malloc");
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		builtin_error("pwd", NULL, "getcwd");
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

static void	update_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_map_value("PWD");
	set_map_overwrite("OLDPWD", oldpwd);
	free(oldpwd);
}

static int	update_pwd(void)
{
	char	*newpwd;

	newpwd = ft_getcwd();
	if (newpwd != NULL)
	{
		remove_private_prefix(newpwd);
		set_map("PWD", newpwd);
	}
	free(newpwd);
	return (0);
}

int	builtin_cd(t_node *node)
{
	int		argc;
	char	*newpwd;
	bool	print_newdir;

	print_newdir = false;
	argc = arglen(node->command->args);
	if (argc >= 3)
	{
		builtin_error("cd", NULL, "too many arguments");
		return (1);
	}
	newpwd = resolve_new_dir(node->command->args->next, argc, &print_newdir);
	if (newpwd == NULL)
		return (1);
	update_oldpwd();
	if (chdir(newpwd) != 0)
	{
		builtin_error("cd", newpwd, strerror(errno));
		free(newpwd);
		return (1);
	}
	if (print_newdir)
		ft_putendl_fd(newpwd, STDOUT_FILENO);
	free(newpwd);
	return (update_pwd());
}
