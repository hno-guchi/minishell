/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:20 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 11:50:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search_path.h"

char	*search_path(const char *file_name)
{
	char	*env_path;
	char	*tail_p;
	char	target[PATH_MAX];

	env_path = getenv("PATH");
	while (env_path)
	{
		bzero(target, PATH_MAX);
		tail_p = strchr(env_path, ':');
		if (tail_p != NULL)
		{
			strncpy(target, env_path, tail_p - env_path);
		}
		else
		{
			strlcpy(target, env_path, PATH_MAX);
		}
		strlcat(target, "/", PATH_MAX);
		strlcat(target, file_name, PATH_MAX);
		if (access(target, X_OK) == 0)
		{
			char	*dup;

			dup = strdup(target);
			if (dup == NULL)
			{
				fatal_error("strdup");
			}
			return (dup);
		}
		if (tail_p == NULL)
		{
			return (NULL);
		}
		env_path = tail_p + 1;
	}
	return (NULL);
}
