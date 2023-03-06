/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_on_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:49:33 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 16:59:24 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("sample$ ");
		if (line == NULL)
		{
			break ;
		}
		if (0 < strlen(line))
		{
			add_history(line);
		}
		// 改行が入力されると、更新関数に伝える。
		if (rl_on_new_line() == 0)
		{
			write(STDOUT_FILENO, "Occure [rl_on_new_line();]\n", 27);
		}
		free(line);
	}
	exit (EXIT_SUCCESS);
}
