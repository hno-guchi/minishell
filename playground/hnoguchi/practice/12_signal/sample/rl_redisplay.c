/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_redisplay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:29:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 16:49:03 by hnoguchi         ###   ########.fr       */
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
		// rl_line_buffer（行バッファ）の現在位置に文字列を挿入する。
		if (0 < rl_insert_text("INSERT TEXT\n"))
		{
			// rl_line_buffer（行バッファ）の現在の内容を出力する。
			rl_redisplay();
		}
		free(line);
	}
	exit (EXIT_SUCCESS);
}
