/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:21:42 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/10 15:40:27 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_signal(void)
{
	if (g_minishell.sig == 0)
	{
		return (0);
	}
	else if (g_minishell.sig == SIGINT)
	{
		g_minishell.sig = 0;
		g_minishell.readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
