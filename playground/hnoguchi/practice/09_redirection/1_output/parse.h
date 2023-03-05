/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:46:22 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/09 15:06:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258

#include <unistd.h>

typedef enum s_node_kind t_node_kind;
typedef struct s_token t_token;
typedef struct s_node t_node;
typedef struct s_redirect t_redirect;

typedef enum s_node_kind {
	NODE_SIMPLE_CMD,
	NODE_REDIR_OUT
}	t_node_kind;

typedef struct s_redirect {
	char	*file_name;
	int		file_fd;
	t_redirect	*next;
}	t_redirect;

typedef struct s_node {
	t_node_kind	kind;
	// CMD
	t_token		*args;
	// REDIR
	// t_redirect	*redirects;
	t_node		*redirects;
	int			target_fd;
	int			stashed_target_fd;
	t_node		*next;
}	t_node;

void	free_node(t_node *node);

// error.c
void	fatal_error(char *fmt, ...);
void	todo(const char *message);

#endif
