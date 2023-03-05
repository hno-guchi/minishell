/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:19:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/10 17:28:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	open_wrap(char *file_name, int flags, mode_t mode)
{
	int	fd;

	fd = open(file_name, flags, mode);
	if (fd < 0)
	{
		exit (EXIT_FAILURE);
	}
	return (fd);
}

int	main(void)
{
	int	fd;

	fd = open_wrap("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		dprintf(STDERR_FILENO, "[FAILED OPEN]...\n");
		exit (EXIT_FAILURE);
	}
	dprintf(STDOUT_FILENO, "[SUCCESS OPEN] create sample.txt\n");
	exit (EXIT_SUCCESS);
}
