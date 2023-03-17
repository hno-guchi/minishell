/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:17:15 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 15:41:13 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
#include "libft.h"
#include <stdbool.h>
#include <stdio.h>

static void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

static bool	is_builtin(const char *command)
{
	if (command == NULL)
	{
		fatal_error("is_builtin");
	}
	else if (ft_strcmp(command, "echo") == 0)
		return (true);
	else if (ft_strcmp(command, "cd") == 0)
		return (true);
	else if (ft_strcmp(command, "pwd") == 0)
		return (true);
	else if (ft_strcmp(command, "export") == 0)
		return (true);
	else if (ft_strcmp(command, "unset") == 0)
		return (true);
	else if (ft_strcmp(command, "env") == 0)
		return (true);
	else if (ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fatal_error("Please argument. [builtin command]");
	}
	if (is_builtin(argv[1]))
	{
		printf("[%s] is builtin command.\n", argv[1]);
	}
	else
	{
		printf("[%s] is not builtin command.\n", argv[1]);
	}
	exit(EXIT_SUCCESS);
}
