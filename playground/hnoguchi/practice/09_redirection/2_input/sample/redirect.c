/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/10 11:18:27 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_fd t_fd;

typedef struct s_fd {
	char	*file_name;
	int		file_fd;
	int		stashed_file_fd;
	t_fd	*next;
}	t_fd;

static int	stash_fd(int fd)
{
	int	stash_fd;

	stash_fd = fcntl(fd, F_DUPFD, 10);
	if (stash_fd < 0)
	{
		dprintf(STDERR_FILENO, "stash_fd: fcntl();");
		exit(EXIT_FAILURE);
	}
	if (close(fd) < 0)
	{
		dprintf(STDERR_FILENO, "stash_fd: close();");
		exit(EXIT_FAILURE);
	}
	return (stash_fd);
}

void	open_redirect_file(t_fd *list)
{
	int	count = 3;
	int	i = 0;

	dprintf(STDERR_FILENO, "[OPEN FILE]\n");
	dprintf(STDERR_FILENO, "-------------------------------\n");
	while (i < count)
	{
		list[i].file_fd = open(list[i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (list[i].file_fd == -1)
		{
			dprintf(STDERR_FILENO, "open_redirect_file: open();");
			exit(EXIT_FAILURE);
		}
		list[i].stashed_file_fd = stash_fd(list[i].file_fd);
		dprintf(STDERR_FILENO, "list[%d].file_name       : [%s]\n", i, list[i].file_name);
		dprintf(STDERR_FILENO, "list[%d].file_fd         : [%2d]--->[%s]---> (closed)\n", i, list[i].file_fd, list[i].file_name);
		dprintf(STDERR_FILENO, "list[%d].stashed_file_fd : [%2d]--->[%s]\n", i, list[i].stashed_file_fd, list[i].file_name);
		if (i != (count - 1))
		{
			dprintf(STDERR_FILENO, "\n");
		}
		i += 1;
	}
	dprintf(STDERR_FILENO, "-------------------------------\n\n");
}

void	do_redirect(int target_fd, t_fd *list)
{
	int	i = 0;
	int	count = 3;

	dprintf(STDERR_FILENO, "[DO REDIRECT]\n");
	list[3].stashed_file_fd = stash_fd(target_fd);
	dprintf(STDERR_FILENO, "target_fd                : [%2d]--->[STDOUT_FILENO]---> (closed)\n", target_fd);
	dprintf(STDERR_FILENO, "stashed_target_fd        : [%2d]--->[%s]\n", list[3].stashed_file_fd, list[3].file_name);
	dprintf(STDERR_FILENO, "-------------------------------\n");
	while (i < count)
	{
		if (list[i].stashed_file_fd != target_fd)
		{
			if (0 < i)
			{
				if (close(target_fd) < 0)
				{
					dprintf(STDERR_FILENO, "do_redirect: close(target_fd);");
					exit(EXIT_FAILURE);
				}
				dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]---> (closed)\n", target_fd, list[i - 1].file_name);
			}
			if (dup2(list[i].stashed_file_fd, target_fd) < 0)
			{
				dprintf(STDERR_FILENO, "do_redirect: dup2();");
				exit(EXIT_FAILURE);
			}
			if (close(list[i].stashed_file_fd) < 0)
			{
				dprintf(STDERR_FILENO, "do_redirect: close();");
				exit(EXIT_FAILURE);
			}
			dprintf(STDERR_FILENO, "list[%d].stashed_file_fd : [%2d]--->[%s]---> (closed)\n", i, list[i].stashed_file_fd, list[i].file_name);
			dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]\n", target_fd, list[i].file_name);
			if (i != (count - 1))
			{
				dprintf(STDERR_FILENO, "\n");
			}
		}
		i += 1;
	}
	dprintf(STDERR_FILENO, "-------------------------------\n\n");
}

void	reset_redirect(int target_fd, t_fd *list)
{
	dprintf(STDERR_FILENO, "[RESET REDIRECT]\n");
	dprintf(STDERR_FILENO, "-------------------------------\n\n");
	if (close(target_fd) < 0)
	{
		dprintf(STDERR_FILENO, "reset_redirect: close(target_fd);");
		exit(EXIT_FAILURE);
	}
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]---> (closed)\n", target_fd, list[2].file_name);
	if (dup2(list[3].stashed_file_fd, target_fd) < 0)
	{
				exit(EXIT_FAILURE);
			// fatal_error("reset_redirect: dup2();");
	}
	if (close(list[3].stashed_file_fd) < 0)
	{
			// fatal_error("reset_redirect: close();");
				exit(EXIT_FAILURE);
	}
	// if (close(node->target_fd) < 0)
	// {
	// 		fatal_error("reset_redirect: close();");
	// }
	dprintf(STDERR_FILENO, "list[3].stashed_file_fd : [%2d]--->[%s]---> (closed)\n", list[3].stashed_file_fd, list[3].file_name);
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]\n", target_fd, list[3].file_name);
}

int	main(void)
{
	t_fd	list[4];

	list[0].file_name = strdup("f1");
	list[0].file_fd = 0;
	list[0].stashed_file_fd = 0;
	list[1].file_name = strdup("f2");
	list[1].file_fd = 0;
	list[1].stashed_file_fd = 0;
	list[2].file_name = strdup("f3");
	list[2].file_fd = 0;
	list[2].stashed_file_fd = 0;
	list[3].file_name = strdup("STDOUT_FILENO");
	list[3].file_fd = 0;
	list[3].stashed_file_fd = 0;

	open_redirect_file(list);
	do_redirect(STDOUT_FILENO, list);
	dprintf(STDOUT_FILENO, "HELLO, WORLD[1]");
	reset_redirect(STDOUT_FILENO, list);
	dprintf(STDOUT_FILENO, "\n\nHELLO, WORLD[2]");
}
