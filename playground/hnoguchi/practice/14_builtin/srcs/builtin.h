/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/19 19:44:02 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
// #include <stdlib.h>

typedef struct s_item		t_item;
typedef struct s_environ	t_environ;

struct s_item {
	char	*name;
	char	*value;
	t_item	*next;
};

struct s_environ {
	t_item	*head_p;
};

t_environ	*g_env;


void		fatal_error(const char *message);
t_environ	*new_map(void);
t_item		*new_item(char *name, char *value);
char		*get_map_value(const char *name);
int			put_map(const char *string);
int			set_map(const char *name, const char *value);
int			unset_map(const char *name);
void		frees_item(t_item *item);
void		frees_map(void);
void		frees_env(char **env);
void		initialize_set_env_map(void);
char		**create_minishell_env(void);

#endif
