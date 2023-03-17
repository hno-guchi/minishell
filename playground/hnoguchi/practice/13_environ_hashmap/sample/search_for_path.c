/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:06:08 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 12:16:06 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}
*/

void	search_for_path(const char *path)
{
	struct stat	stat_buf;

	errno = 0;
	if (stat(path, &stat_buf) < 0)
	{
		dprintf(STDERR_FILENO, "stat();\n");
		dprintf(STDERR_FILENO, "------------------------\n");
		if (errno == 20)
		{
			dprintf(STDERR_FILENO, "exit status == [126];\n");
			dprintf(STDERR_FILENO, "Not a directory\n");
		}
		else if (errno == 2)
		{
			dprintf(STDERR_FILENO, "exit status == [127];\n");
			dprintf(STDERR_FILENO, "No such file or directory\n");
		}
		else
		{
			dprintf(STDERR_FILENO, "exit status == [127];\n");
			dprintf(STDERR_FILENO, "No such file or directory\n");
		}
		dprintf(STDERR_FILENO, "errno == [%d];\n", errno);
		perror(path);
		dprintf(STDERR_FILENO, "------------------------\n\n");
	}
	if (S_ISDIR(stat_buf.st_mode))
	{
		dprintf(STDERR_FILENO, "S_ISDIR();\n");
		dprintf(STDERR_FILENO, "------------------------\n");
		dprintf(STDERR_FILENO, "exit status == [126];\n");
		dprintf(STDERR_FILENO, "is a directory\n");
		dprintf(STDERR_FILENO, "errno == [%d];\n", errno);
		perror(path);
		dprintf(STDERR_FILENO, "------------------------\n\n");
	}
	if (access(path, X_OK) < 0)
	{
		dprintf(STDERR_FILENO, "access(X_OK);\n");
		dprintf(STDERR_FILENO, "------------------------\n");
		if (errno == 13)
		{
			dprintf(STDERR_FILENO, "exit status == [126];\n");
			dprintf(STDERR_FILENO, "Permission denied\n");
		}
		else
		{
			dprintf(STDERR_FILENO, "exit status == [127];\n");
			dprintf(STDERR_FILENO, "No such file or directory\n");
		}
		dprintf(STDERR_FILENO, "errno == [%d];\n", errno);
		perror(path);
		dprintf(STDERR_FILENO, "------------------------\n\n");
	}
	if (access(path, R_OK) < 0)
	{
		dprintf(STDERR_FILENO, "access(R_OK);\n");
		dprintf(STDERR_FILENO, "------------------------\n");
		dprintf(STDERR_FILENO, "errno == [%d];\n", errno);
		perror(path);
		dprintf(STDERR_FILENO, "------------------------\n\n");
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Please argument...[file_path_name]\n");
		exit (EXIT_FAILURE);
	}
	search_for_path(argv[1]);
	exit (EXIT_SUCCESS);
}
