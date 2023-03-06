/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_clear_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:59:39 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 17:31:02 by hnoguchi         ###   ########.fr       */
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
		if (strcmp(line, "clear") == 0)
		{
			// それまで、保持していた履歴を削除する。
			rl_clear_history();
		}
		free(line);
	}
	exit (EXIT_SUCCESS);
}
