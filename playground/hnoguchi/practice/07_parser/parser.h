/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:46:22 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/03 11:36:44 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum s_node_kind t_node_kind;
typedef struct s_token t_token;
typedef struct s_node t_node;

typedef enum s_node_kind {
	NODE_SIMPLE_COMMAND
}	t_node_kind;

typedef struct s_node {
	t_token		*args;
	t_node_kind	kind;
	t_node		*next;
}	t_node;

t_node	*parser(t_token *token);
void	free_node(t_node *node);

// error.c
void	fatal_error(char *fmt, ...);
void	todo(const char *message);

#endif
