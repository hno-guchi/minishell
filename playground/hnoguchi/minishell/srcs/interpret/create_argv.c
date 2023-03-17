/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:57:50 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 14:23:13 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_token_word(size_t *size, t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
		{
			*size += 1;
		}
		token = token->next;
	}
}

char	**create_argv(char *path, t_token *token)
{
	char	**argv;
	size_t	i;
	size_t	size;
	t_token	*head_p;

	i = 1;
	size = 0;
	head_p = token->next;
	count_token_word(&size, token);
	token = head_p;
	argv = ft_calloc(size + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	argv[0] = path;
	while (token != NULL)
	{
		if (token->word != NULL)
		{
			argv[i] = ft_strdup(token->word);
			i += 1;
		}
		token = token->next;
	}
	return (argv);
}
