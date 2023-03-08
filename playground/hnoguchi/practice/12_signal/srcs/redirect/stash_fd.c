/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:59:04 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_used_fd(int fd)
{
	struct stat	*buf;

	buf = NULL;
	if (fd < 0)
	{
		return (false);
	}
	errno = 0;
	if (fstat(fd, buf) < 0)
	{
		if (errno == EBADF)
		{
			return (false);
		}
	}
	return (true);
}

int	stash_fd(int fd)
{
	int	stash_fd;

	stash_fd = 10;
	if (fd < 0)
	{
		fatal_error("fd");
	}
	while (is_used_fd(stash_fd))
	{
		stash_fd += 1;
	}
	if (dup2(fd, stash_fd) < 0)
	{
		fatal_error("dup2");
	}
	if (close(fd) < 0)
	{
		fatal_error("close");
	}
	return (stash_fd);
}
