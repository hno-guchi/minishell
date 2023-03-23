/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:07 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/23 13:46:29 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define SIZE_OPERATOR_LIST 5
# define SIZE_CONTROL_LIST 1
# define SIZE_REDIRECTION_LIST 4
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

typedef enum e_token_kind	t_token_kind;
typedef enum e_redir_kind	t_redir_kind;
typedef enum e_node_kind	t_node_kind;
typedef struct s_minishell	t_minishell;
typedef struct s_token		t_token;
typedef struct s_node		t_node;
typedef struct s_item		t_item;
typedef struct s_environ	t_environ;

extern t_minishell			g_minishell;

enum e_token_kind {
	TK_WORD,
	TK_CONTROL,
	TK_REDIRECTION,
	TK_EOF
};

enum e_redir_kind {
	REDIR_NOT,
	REDIR_IN,
	REDIR_HERE_DOC,
	REDIR_EXPAND_HERE_DOC,
	REDIR_OUT,
	REDIR_APPEND_OUT
};

enum e_node_kind {
	NODE_PIPELINE,
	NODE_SIMPLE_CMD,
	NODE_REDIR_OUT,
	NODE_REDIR_IN
};

typedef struct s_minishell {
	unsigned int			last_status;
	bool					syntax_error;
	bool					readline_interrupted;
	volatile sig_atomic_t	sig;
	t_environ				*env;
}	t_minishell;

struct s_token {
	char			*word;
	t_token_kind	kind;
	t_redir_kind	redir_kind;
	int				file_fd;
	int				stashed_file_fd;
	t_token			*next;
};

struct s_node {
	t_node_kind	kind;
	t_node		*command;
	t_token		*args;
	t_node		*redirects;
	int			input_fd;
	int			output_fd;
	t_node		*next;
};

struct s_item {
	char	*name;
	char	*value;
	t_item	*next;
};

struct s_environ {
	t_item	*head_p;
};

// environ dir
t_environ	*new_map(void);
t_item		*new_item(char *name, char *value);
char		*get_map_value(const char *name);
int			set_map(const char *name, const char *value);
int			put_map(const char *string);
int			unset_map(const char *name);
void		frees_item(t_item *item);
void		frees_map(void);
void		frees_env(char **env);
void		initialize_set_env_map(void);
char		**create_env(void);

// error dir
void		fatal_error(const char *message) __attribute__((noreturn));
void		error_message(const char *location, const char *message,
				int status) __attribute__((noreturn));
void		assert_error(const char *message) __attribute__((noreturn));
void		tokenize_error(char location, char **rest, char *line);
void		parse_error(t_token **rest, t_token *token);
void		xperror(const char *location);
void		error_number_message(const char *word, int num);

// expand dir
t_node		*expand(t_node *node);
bool		is_alnum_underscore(const char c);
bool		is_variable(const char *str);
bool		is_special_parameter(const char *str);
void		add_character(char **word, char c);
void		try_remove_quote(t_token *token);
void		append_variable(char **new_word, char **rest, char *current_word);
void		append_special_param(char **new_word, char **rest,
				char *current_word);

// interpret dir
bool		is_builtin(const char *command);
int			interpret(t_node *node);
char		*create_path(char *word);
char		**create_argv(char *path, t_token *token);
int			exec_builtin(t_node *node);
int			exec_pipeline(t_node *node, int *prev_fd);
int			wait_pipeline(pid_t last_pid);

// parse dir
t_node		*parse(t_token *token);
bool		is_quote(const char *str);
t_node		*new_node(t_node_kind kind);
t_token		*token_dup(t_redir_kind redir_kind, t_token *source);
bool		at_eof(t_token_kind kind);
void		append_args(t_token **args, t_token *add_token);
void		append_redirects(t_node **redir, t_token *add_token,
				t_node_kind kind);
void		list_add_back(t_node **redir, t_token *add_token, t_node_kind kind);
void		try_append_redirect(t_node *node, t_token **rest, t_token *token);

// pipe dir
void		prepare_pipe(t_node *node, int *next_input, int *output);
void		prepare_pipe_child(int *input, int *output);
void		close_pipe_parent(t_node *node, int *input, int *output);

// redirect dir
int			stash_fd(int fd);
void		reset_close(int	*target_fd);
int			open_redir_file(t_node *node);
void		redirect_file(t_node *command);
void		reset_redirect_command(t_node *command);
void		closes_redirect_file(t_node *node);
int			read_here_document(t_token *token);
void		reset_redirect_command(t_node *command);

// signal dir
void		initialize_sa(int signal, struct sigaction *sa);
void		initialize_signals(void);
void		set_signals_receiver(void);
void		set_signals_default(void);
void		signal_default_handler(int signal);
void		set_signals_ignore(void);
void		signal_ignore_handler(int signal);

// tokenize dir
t_token		*tokenize(char *line);
bool		is_blank(char c);
bool		is_meta_character(const char c);
t_token		*new_token(t_token_kind kind, t_redir_kind redir_kind, char *word);
t_token		*new_token_type_word(char **rest, char *line);
t_token		*new_token_type_operator(char **rest, char *line);

// destructor.c
void		frees_argv(char **argv);
void		list_frees_token(t_token *token);
void		list_frees_node(t_node *node);

#endif
