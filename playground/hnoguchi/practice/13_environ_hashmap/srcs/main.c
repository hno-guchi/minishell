/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 12:07:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_environ	*g_env;

static void	print_env_map()
{
	size_t	count;
	t_item	*item;

	count = 0;
	item = g_env->head_p;
	printf("===============================\n");
	while (item != NULL)
	{
		printf("\n+[%2ld]+++++++++++++++++++++++\n", count);
		printf("item->name  : [%s]\n", item->name);
		printf("item->value : [%s]\n", item->value);
		item = item->next;
		count += 1;
	}
	printf("===============================\n");
}

static void	print_minishell_env(char **env)
{
	// size_t	i;

	// i = 0;
	while(*env != NULL)
	{
		// printf("env[%2ld] : [%s]\n", i, *env);
		printf("%s\n", *env);
		// i += 1;
		env += 1;
	}
}

int	main(void)
{
	char	**minishell_env;

	minishell_env = NULL;

	initialize_set_env_map();
	print_env_map();

	minishell_env = create_minishell_env();
	print_minishell_env(minishell_env);

	frees_map();
	frees_env(minishell_env);
	system("leaks -q minishell");
	exit(EXIT_SUCCESS);
}

/*
// TEST new_map(); new_item();
int	main(void)
{
	t_environ	*env;
	t_item		*item;

	env = new_map();
	printf("env->head_p->name  : [%s]\n", env->head_p->name);
	printf("env->head_p->value : [%s]\n", env->head_p->value);
	printf("env->head_p->next  : [%p]\n\n", env->head_p->next);

	item = new_item("USER", "hnoguchi");
	printf("item->name  : [%s]\n", item->name);
	printf("item->value : [%s]\n", item->value);
	printf("item->next  : [%p]\n\n", item->next);
	frees_item(item);

	item = new_item("TEST", NULL);
	printf("item->name  : [%s]\n", item->name);
	printf("item->value : [%s]\n", item->value);
	printf("item->next  : [%p]\n\n", item->next);
	frees_item(item);

	item = new_item(NULL, "value");
	if (item != NULL)
	{
		printf("item->name  : [%s]\n", item->name);
		printf("item->value : [%s]\n", item->value);
		printf("item->next  : [%p]\n\n", item->next);
		frees_item(item);
	}

	item = new_item(NULL, NULL);
	if (item != NULL)
	{
		printf("item->name  : [%s]\n", item->name);
		printf("item->value : [%s]\n", item->value);
		printf("item->next  : [%p]\n\n", item->next);
		frees_item(item);
	}
	// system("leaks -q minishell");
	exit(EXIT_SUCCESS);
}
*/
