/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/08 15:27:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// main.c
// #include <unistd.h>

// tokenize.c
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parse.c
// #include <unistd.h>

// redirect.c
// #include <unistd.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
#include <fcntl.h>

// search_path.c
#include <limits.h>

// interpret.c
#include <errno.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define SIZE_OPERATORS_LIST 13
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define ERROR_PREFIX "minishell: "

typedef enum s_node_kind t_node_kind;
typedef struct s_token t_token;
typedef struct s_node t_node;
typedef enum s_token_kind t_token_kind;

typedef enum s_token_kind {
	TK_WORD,
	TK_RESERVED,
	TK_OPERATOR,
	TK_EOF
}	t_token_kind;

typedef enum s_node_kind {
	NODE_PIPELINE,
	NODE_SIMPLE_CMD,
	NODE_REDIR_OUT,
	NODE_REDIR_IN
}	t_node_kind;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	int				file_fd;
	int				stashed_file_fd;
	t_token			*next;
}	t_token;

typedef struct s_node {
	t_node_kind	kind;
	// int			pipe_fd[2];
	// CMD
	t_node		*command;
	t_token		*args;
	// REDIR
	t_node		*redirects;
	int			input_fd;
	int			output_fd;
	t_node		*next;
}	t_node;

// tokenize.c
t_token	*tokenize(char *line);

// is_func.c
bool	is_blank(char c);
bool	consume_blank(char **rest, char *line);
bool	is_meta_character(const char c);
bool	is_operator(char *str, const char *operator);
bool	is_word(char c);

// new_token.c
t_token	*new_token(t_token_kind kind, char *word);
t_token	*new_token_type_operator(char **rest, char *line);
t_token	*new_token_type_word(char **rest, char *line);

// parse.c
t_node	*parse(t_token *token);
void	free_node(t_node *node);

// error_func.c
void	assert_error(const char *message);
void	fatal_error(const char *message);
void	todo(const char *message);
void	error_message(const char *location, const char *message, int status);
void	xperror(const char *location);

// search_path.c
char	*search_path(const char *file_name);

// expand.c
t_node	*expand(t_node *node);

// pipe.c
void	prepare_pipe(t_node *node, int *pipe_fd);
void	prepare_pipe_child(t_node *node, int *pipe_fd, int *prev_fd);
void	prepare_pipe_parent(t_node *node, int *pipe_fd);
// void	prepare_pipe(int *pipe_fd);
// void	prepare_pipe_child(t_node *node, int *pipe_fd, int *prev_fd);
// void	prepare_pipe_parent(int *pipe_fd);

// redirect.c
int		open_redir_file(t_node *node);
void	redirect_file(t_node *command);
// void	redirect(t_node *node);
// void	reset_redirect_node(t_node *node);
void	reset_redirect_command(t_node *command);
void	closes_redirect_file(t_node *node);

// interpret.c
int	interpret(t_node *node);

// print_result.c
// main()
void	print_token(t_token *token, const char *message);
void	print_result_token(t_token *token, const char *message);
void	print_result_redirects(t_node *list, const char *message);
void	print_result_parse(t_node *node, char *message);
void	print_result_expand(t_node *node, char *message);
void	print_result_redirect(t_node *node);
// redirect()
void	do_print_result_redir(t_token *token);
void	print_result_open_redir(t_token *token, char *message);
void	print_result_close_redir(int *target_fd, t_token *token, char *message);
// interpret.c
void	print_result_create_argv(char **argv);
// print_result_pipe.c
void	print_result_prepare_pipe(t_node *node);
void	print_before_prepare_pipe_child(int *pipe_fd, int *prev_fd);

// destructor.c
void	list_frees_token(t_token *token);
void	list_frees_redirects(t_node *list);
void	list_frees_node(t_node *node);

# endif
