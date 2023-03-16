/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:19:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/16 11:56:18 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
#include "libft.h"
#include <stdio.h>

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
void		frees_item(t_item *item);
void		frees_map(void);
void		frees_env(char **env);
void		initialize_set_env_map(void);
char		**create_minishell_env(void);

#endif
