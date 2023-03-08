/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:07 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/02 10:48:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

// main.c
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// tokenize.c
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// parse.c
// #include <unistd.h>

// expand.c
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// redirect.c
// #include <unistd.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
#include <fcntl.h>
#include <sys/stat.h>

// interpret.c
#include <errno.h>

// signal.c
#include <unistd.h>
#include <signal.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define SIZE_OPERATORS_LIST 13
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

typedef enum s_token_kind t_token_kind;
typedef enum s_node_kind t_node_kind;
typedef struct s_minishell t_minishell;
typedef struct s_token t_token;
typedef struct s_node t_node;

extern t_minishell	g_minishell;

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

typedef struct s_minishell {
	unsigned int			last_status;
	bool					syntax_error;
	bool					readline_interrupted;
	volatile sig_atomic_t	sig;
}	t_minishell;

typedef struct s_token {
	char			*word;
	t_token_kind	kind;
	int				file_fd;
	int				stashed_file_fd;
	t_token			*next;
}	t_token;

typedef struct s_node {
	t_node_kind	kind;
	// CMD
	t_node		*command;
	t_token		*args;
	// REDIR
	t_node		*redirects;
	int			input_fd;
	int			output_fd;
	t_node		*next;
}	t_node;

// signal.c
void	setup_signals(void);
void	reset_signal_handler(void);

// error_func.c
void	fatal_error(const char *message) __attribute__((noreturn));
void	error_message(const char *location, const char *message, int status) __attribute__((noreturn));
void	assert_error(const char *message) __attribute__((noreturn));
void	tokenize_error(char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *token);
void	xperror(const char *location);

// destructor.c
void	frees_argv(char **argv);
void	list_frees_token(t_token *token);
void	list_frees_node(t_node *node);

// tokenize.c
t_token	*tokenize(char *line);
t_token	*new_token(t_token_kind kind, char *word);

// parse.c
t_node	*parse(t_token *token);
bool	at_eof(t_token_kind kind);

// expand.c
t_node	*expand(t_node *node);

// redirect.c
int		open_redir_file(t_node *node);
void	redirect_file(t_node *command);
void	reset_redirect_command(t_node *command);
void	closes_redirect_file(t_node *node);

// pipe.c
void	prepare_pipe(int *pipe_fd);
void	prepare_pipe_child(t_node *node, int *pipe_fd, int *prev_fd);
void	prepare_pipe_parent(int *pipe_fd);

// search_path.c
char	*search_path(const char *file_name);

// interpret.c
int		interpret(t_node *node);

// print_result.c
// void	print_result_token(t_token *token, const char *message);
// void	print_result_redirects(t_node *list, const char *message);
// void	print_result_parse(t_node *node, char *message);
// void	print_result_expand(t_node *node, char *message);
// void	print_result_redirect(t_node *node);

#endif
