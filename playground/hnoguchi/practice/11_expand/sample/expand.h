/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:04:13 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/26 16:16:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef enum s_token_kind t_token_kind;
typedef struct s_token t_token;

typedef enum s_token_kind {
	TK_WORD
}	t_token_kind;

typedef struct s_token {
	t_token_kind	kind;
	char 			*word;
	int				last_status;
	t_token			*next;
}	t_token;

// variable.c
bool	is_variable(const char *str);
void	add_character(char **word, char c);
void	append_variable_str(char **new_word, char **rest, char *current_word);
void	fatal_error(const char *message);

// special_param.c
bool	is_special_parameter(const char *str);
void	append_special_param(char **new_word, int status, char **rest, char *current_word);
#endif
