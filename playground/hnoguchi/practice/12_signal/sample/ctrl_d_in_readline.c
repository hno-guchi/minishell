/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_in_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:32:01 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/15 11:42:31 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("sample> ");
		if (RL_ISSTATE(RL_STATE_EOF))
		{
			dprintf(STDOUT_FILENO, "logout\n");
			break ;
		}
		else if (line == NULL)
		{
			break ;
		}
		if (strcmp(line, "<< EOF") == 0)
		{
			char	*heredoc;

			while (1)
			{
				heredoc = readline("> ");
				if (RL_ISSTATE(RL_STATE_EOF))
				{
					break ;
				}
				if (heredoc == NULL)
				{
					break ;
				}
				printf("heredoc[%s];\n", heredoc);
				free(heredoc);
			}
			free(line);
			continue ;
		}
		printf("%s\n", line);
		free(line);
	}
	exit (EXIT_SUCCESS);
}
