/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/11 17:42:47 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SIZE_OPERATORS_LIST 9
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

typedef struct s_token t_token;
typedef struct s_node t_node;
typedef enum s_token_kind t_token_kind;

typedef enum s_token_kind {
	TK_WORD,
	// TK_NAME,
	TK_RESERVED,
	TK_OPERATOR,
	// TK_REDIR_APPEND_OUT,
	// TK_REDIR_OUT,
	TK_EOF
}	t_token_kind;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	int				file_fd;
	int				stashed_file_fd;
	t_token			*next;
}	t_token;

// is_func.c
bool	is_blank(char c);
bool	consume_blank(char **rest, char *line);
bool	is_meta_character(const char c);
bool	is_operator(char *str, const char *operator);
bool	is_word(char c);

// error.c
void	fatal_error(char *fmt, ...);
void	todo(const char *message);

// new_token.c
t_token	*new_token(t_token_kind kind, char *word);
t_token	*new_token_type_operator(char **rest, char *line);
t_token	*new_token_type_word(char **rest, char *line);

// tokenize.c
t_token	*tokenize(char *line);

// expand.c
t_node	*expand(t_node *node);

# endif
