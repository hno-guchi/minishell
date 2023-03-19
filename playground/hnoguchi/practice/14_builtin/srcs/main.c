/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:17:15 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/19 19:51:28 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static int	exec_builtin(const char *command)
{
	int	status;

	status = 0;
	if (command == NULL)
	{
		fatal_error("is_builtin");
	}
	else if (ft_strcmp(command, "echo") == 0)
		;
	else if (ft_strcmp(command, "cd") == 0)
		;
	else if (ft_strcmp(command, "pwd") == 0)
		;
	else if (ft_strcmp(command, "export") == 0)
	{
		status = export_builtin();
	}
	else if (ft_strcmp(command, "unset") == 0)
		;
	else if (ft_strcmp(command, "env") == 0)
		;
	else if (ft_strcmp(command, "exit") == 0)
		;
	return (status);
}

int	main(int argc, char **argv)
{
	int	status;

	status = 0;
	if (argc != 2)
	{
		fatal_error("Please argument. [builtin command]");
	}
	if (is_builtin(argv[1]))
	{
		status = exec_builtin(argv[1]);
	}
	else
	{
		printf("[%s] is not builtin command.\n", argv[1]);
	}
	printf("status [%d]\n", status);
	exit(EXIT_SUCCESS);
}
