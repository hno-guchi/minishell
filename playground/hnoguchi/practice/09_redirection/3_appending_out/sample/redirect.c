/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/11 16:24:16 by hnoguchi         ###   ########.fr       */
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
	char	*stashed_file_name;
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
		dprintf(STDERR_FILENO, "list[%d].file_name       : [%s]\n", i, list[i].file_name);
		dprintf(STDERR_FILENO, "list[%d].file_fd         : [%2d]--->[%13s]---> (closed)\n", i, list[i].file_fd, list[i].file_name);
		list[i].file_fd = stash_fd(list[i].file_fd);
		dprintf(STDERR_FILENO, "list[%d].file_fd         : [%2d]--->[%13s]\n", i, list[i].file_fd, list[i].file_name);
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
	dprintf(STDERR_FILENO, "-------------------------------\n");
	while (i < count)
	{
		if (list[i].file_fd != target_fd)
		{
			list[i].stashed_file_fd = stash_fd(target_fd);
			if (dup2(list[i].file_fd, target_fd) < 0)
			{
				dprintf(STDERR_FILENO, "do_redirect: dup2();");
				exit(EXIT_FAILURE);
			}
			if (close(list[i].file_fd) < 0)
			{
				dprintf(STDERR_FILENO, "do_redirect: close();");
				exit(EXIT_FAILURE);
			}
			if (i == 0)
			{
				list[i].stashed_file_name = strdup("STDOUT_FILENO");
				dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]---> (closed)\n", target_fd, list[i].stashed_file_name);
				dprintf(STDERR_FILENO, "list[%d].stashed_file_fd : [%2d]--->[%s]\n", i, list[i].stashed_file_fd, list[i].stashed_file_name);
			}
			else
			{
				list[i].stashed_file_name = strdup(list[i - 1].file_name);
				dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%13s]---> (closed)\n", target_fd, list[i].stashed_file_name);
				dprintf(STDERR_FILENO, "list[%d].stashed_file_fd : [%2d]--->[%13s]\n", i, list[i].stashed_file_fd, list[i].stashed_file_name);
			}
			dprintf(STDERR_FILENO, "list[%d].file_fd         : [%2d]--->[%13s]---> (closed)\n", i, list[i].file_fd, list[i].file_name);
			dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%13s]\n", target_fd, list[i].file_name);
			if (i != (count - 1))
			{
				dprintf(STDERR_FILENO, "\n");
			}
		}
		i += 1;
	}
	dprintf(STDERR_FILENO, "-------------------------------\n\n");
}

void	reset_recursive_redirect(int target_fd, t_fd *list, int idx)
{
	if (list == NULL)
	{
		return ;
	}
	reset_recursive_redirect(target_fd, list->next, idx + 1);
	if (close(target_fd) < 0)
	{
		dprintf(STDERR_FILENO, "reset_redirect: close(target_fd);");
		exit(EXIT_FAILURE);
	}
	if (dup2(list->stashed_file_fd, target_fd) < 0)
	{
				exit(EXIT_FAILURE);
	}
	if (close(list->stashed_file_fd) < 0)
	{
				exit(EXIT_FAILURE);
	}
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%13s]---> (closed)\n", target_fd, list->file_name);
	dprintf(STDERR_FILENO, "list[%d].stashed_file_fd : [%2d]--->[%13s]---> (closed)\n", idx, list->stashed_file_fd, list->stashed_file_name);
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%13s]\n", target_fd, list->stashed_file_name);
}

/*
void	reset_redirect(int target_fd, t_fd *list)
{
	if (close(target_fd) < 0)
	{
		dprintf(STDERR_FILENO, "reset_redirect: close(target_fd);");
		exit(EXIT_FAILURE);
	}
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]---> (closed)\n", target_fd, list[2].file_name);
	if (dup2(list[3].stashed_file_fd, target_fd) < 0)
	{
				exit(EXIT_FAILURE);
	}
	if (close(list[3].stashed_file_fd) < 0)
	{
				exit(EXIT_FAILURE);
	}
	// if (close(node->target_fd) < 0)
	// {
	// 		fatal_error("reset_redirect: close();");
	// }
	dprintf(STDERR_FILENO, "list[3].stashed_file_fd : [%2d]--->[%s]---> (closed)\n", list[3].stashed_file_fd, list[3].file_name);
	dprintf(STDERR_FILENO, "target_fd               : [%2d]--->[%s]\n", target_fd, list[3].file_name);
}
*/

int	main(void)
{
	t_fd	list[3];

	list[0].file_name = strdup("f1");
	list[0].file_fd = 0;
	list[0].stashed_file_name = NULL;
	list[0].stashed_file_fd = 0;
	list[0].next = &list[1];

	list[1].file_name = strdup("f2");
	list[1].file_fd = 0;
	list[1].stashed_file_name = NULL;
	list[1].stashed_file_fd = 0;
	list[1].next = &list[2];

	list[2].file_name = strdup("f3");
	list[2].file_fd = 0;
	list[2].stashed_file_name = NULL;
	list[2].stashed_file_fd = 0;
	list[2].next = NULL;

	open_redirect_file(list);
	do_redirect(STDOUT_FILENO, list);

	dprintf(STDOUT_FILENO, "HELLO, WORLD[1]");

	dprintf(STDERR_FILENO, "[RESET REDIRECT]\n");
	dprintf(STDERR_FILENO, "-------------------------------\n");
	reset_recursive_redirect(STDOUT_FILENO, list, 0);
	dprintf(STDERR_FILENO, "-------------------------------\n");
	// reset_redirect(STDOUT_FILENO, list);
	dprintf(STDOUT_FILENO, "\nHELLO, WORLD[2]");
}
