/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/17 19:35:19 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_environ	*g_env;

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

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

// TEST put_map(); set_map(); unset_map();
int	main(void)
{
	initialize_set_env_map();

	put_map("TEST1=value1");
	put_map("TEST2=value2");
	put_map("TEST3=value3");
	put_map("TEST4=value4");
	put_map("TEST5=value5");
	put_map("TEST6=value6");
	put_map("TEST7=value7");
	put_map("TEST8=value8");
	put_map("not_equol");
	put_map("not_value=");

	unset_map("TEST1");
	unset_map("TEST3");
	unset_map("TEST7");
	unset_map("TEST8");
	unset_map("not_equol");
	unset_map("not_value");
	unset_map("NOT_NAME");

	print_env_map();
	frees_map();
	// system("leaks -q minishell");
	exit(EXIT_SUCCESS);
}

/*
// TEST get_map_value();
int	main(void)
{
	char	*get_value;

	get_value = NULL;
	initialize_set_env_map();

	get_value = get_map_value("PATH");
	printf("get_value : PATH : [%s]\n", get_value);
	free(get_value);

	get_value = get_map_value("USER");
	printf("get_value : USER : [%s]\n", get_value);
	free(get_value);

	get_value = get_map_value("NOT");
	printf("get_value : NOT  : [%s]\n", get_value);
	free(get_value);

	get_value = get_map_value("");
	printf("get_value : \"\"   : [%s]\n", get_value);
	free(get_value);

	get_value = get_map_value(NULL);
	printf("get_value : NULL : [%s]\n", get_value);
	free(get_value);

	print_env_map();
	frees_map();
	// system("leaks -q minishell");
	exit(EXIT_SUCCESS);
}
*/

/*
// TEST initialize_set_env_map();
// TEST minishell_env();
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
*/
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
