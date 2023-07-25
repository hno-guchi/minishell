/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_character.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:55 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 15:04:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_character(char **word, char c)
{
	size_t	size;
	char	*temp;

	size = 2;
	temp = NULL;
	if (*word != NULL)
	{
		size += ft_strlen(*word);
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			fatal_error("malloc");
		}
		ft_strlcpy(temp, *word, size);
		free(*word);
	}
	else
	{
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
			fatal_error("malloc");
	}
	temp[size - 2] = c;
	temp[size - 1] = '\0';
	*word = temp;
}
