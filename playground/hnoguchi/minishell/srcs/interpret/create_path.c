/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:20 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/18 17:40:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cat_path_file_name(char *target, const char *file_name,
		char *path_env, char *tail_p)
{
	if (tail_p != NULL)
	{
		ft_strncpy(target, path_env, tail_p - path_env);
	}
	else
	{
		ft_strlcpy(target, path_env, PATH_MAX);
	}
	ft_strlcat(target, "/", PATH_MAX);
	ft_strlcat(target, file_name, PATH_MAX);
}

static char	*do_search(char *path_env, const char *file_name)
{
	char	*path_exec_file;
	char	*tail_p;
	char	target[PATH_MAX];

	path_exec_file = NULL;
	while (path_env != NULL)
	{
		ft_bzero(target, PATH_MAX);
		tail_p = ft_strchr(path_env, ':');
		cat_path_file_name(target, file_name, path_env, tail_p);
		if (access(target, X_OK) == 0)
		{
			path_exec_file = ft_strdup(target);
			if (path_exec_file == NULL)
			{
				fatal_error("ft_strdup");
			}
			return (path_exec_file);
		}
		if (tail_p == NULL)
			return (NULL);
		path_env = tail_p + 1;
	}
	return (NULL);
}

static char	*search_path(const char *file_name)
{
	char	*path_env;
	char	*path_exec_file;

	path_env = get_map_value("PATH");
	path_exec_file = do_search(path_env, file_name);
	free(path_env);
	return (path_exec_file);
}

static int	check_path(const char *path)
{
	struct stat	stat_buf;

	errno = 0;
	if (stat(path, &stat_buf) < 0)
	{
		return (errno);
	}
	else if (S_ISDIR(stat_buf.st_mode))
	{
		return (-1);
	}
	else if (access(path, X_OK) < 0)
	{
		return (errno);
	}
	else if (access(path, R_OK) < 0)
	{
		return (errno);
	}
	return (0);
}

char	*create_path(char *word)
{
	char	*path;
	int		error_number;

	path = NULL;
	error_number = 0;
	if (ft_strchr(word, '/') == NULL)
	{
		path = search_path(word);
		if (path == NULL)
		{
			error_message(word, "command not found", 127);
		}
	}
	else
	{
		path = ft_strdup(word);
		error_number = check_path(path);
		if (error_number != 0)
		{
			free(path);
			error_number_message(word, error_number);
		}
	}
	return (path);
}
