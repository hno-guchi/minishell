/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fstat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:19:05 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/01 18:20:31 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * man fstat
 *
 * #include <sys/stat.h>
 * int	fstat(int fildes, struct stat *buf);
 *
 * The fstat(); obtains the same information about an open file known by the file descriptor [fildes].
 *
 * RETURN VALUES
 * Upon successful completion a value of 0 is returned.
 * Otherwise, a value a -1.
 * Set a errno.
 *
 * ERRORS
 * [EBADF]
 * fildes is not a valid open file descriptor.
 */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit (EXIT_FAILURE);
}

static bool	is_useable_fd(int fd)
{
	struct stat	*buf;

	if (fstat(fd, buf) < 0 && errno == EBADF)
	{
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			result;
	int			stash_fd;

	fd = 0;
	result = 0;
	stash_fd = 10;
	if (argc != 2)
	{
		fatal_error("Not argument...");
	}
	fd = open(argv[1], O_RDONLY);
	while (!is_useable_fd(stash_fd))
	{
		dprintf(STDOUT_FILENO, "Do not exist fd is [%d]\n", stash_fd);
		stash_fd -= 1;
		if (stash_fd < 0)
		{
			break ;
		}
	}
	dprintf(STDOUT_FILENO, "Exist fd number. stash_fd is [%d]\n", stash_fd);
	exit(EXIT_SUCCESS);
}
