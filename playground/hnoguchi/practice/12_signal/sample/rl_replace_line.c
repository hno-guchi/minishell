/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:32:11 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 20:08:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 * https://stackoverflow.com/questions/53165704/readline-c-force-return-of-certain-text-in-readline
 */

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
		rl_replace_line("", 0);
		rl_redisplay();
		free(line);
	}
	exit (EXIT_FAILURE);
}
