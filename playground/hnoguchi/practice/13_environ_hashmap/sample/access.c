/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:32:43 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 19:48:15 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fatal_error("Please argument....");
	}

	if (access(argv[1], F_OK) == 0)
	{
		dprintf(STDOUT_FILENO, "[F_OK] : [%s]\n", argv[1]);
	}
	else
	{
		dprintf(STDERR_FILENO, "[F_OK] : errno [%d]\n", errno);
		perror(argv[1]);
		errno = 0;
	}

	if (access(argv[1], X_OK) == 0)
	{
		dprintf(STDOUT_FILENO, "[X_OK] : [%s]\n", argv[1]);
	}
	else
	{
		dprintf(STDERR_FILENO, "[X_OK] : errno [%d]\n", errno);
		perror(argv[1]);
		errno = 0;
	}
	exit (EXIT_SUCCESS);
}
