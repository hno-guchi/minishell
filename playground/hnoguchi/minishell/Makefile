#############
# Variables #
#############

NAME = minishell
CC = cc
INCLUDES = -I./includes -I./libft/includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LIBRARIES = -lreadline -lhistory -lft -L./libft
G_ADDRESS_FLAGS = -g -fsanitize=address
SRCS = main.c \
	   utils_map.c set_map.c put_map.c create_env.c destructors_map.c initialize_set_env_map.c \
	   error_func.c xperror.c error_number_message.c \
	   expand.c is_func.c add_character.c try_remove_quote.c append_func.c \
	   interpret.c create_path.c create_argv.c exec_builtin.c exec_pipeline.c wait_pipeline.c \
	   parse.c is_quote.c new_node.c at_eof.c list_add_back.c append_args.c append_redirects.c try_append_redirect.c \
	   pipe.c \
	   redirect.c stash_fd.c reset_close.c open_redir_file.c read_here_document.c read_expand_here_document.c closes_redirect_file.c reset_redirect_command.c \
	   initialize_sa.c initialize_signals.c set_signals_default.c set_signals_ignore.c set_signals_receiver.c \
	   tokenize.c new_token.c new_token_type_word.c new_token_type_operator.c\
	   destructor.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))
SRCS_DIR = ./srcs
OBJS_DIR = ./objs

LIBFT_DIR = ./libft

#################
# General Rules #
#################

all: libft $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/environ/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/error/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/expand/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/interpret/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/parse/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/pipe/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/redirect/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/signal/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/tokenize/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

libft:
	make -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean:
	$(RM) -r $(OBJS_DIR)
	$(RM) $(NAME)
	$(RM) test_overflow
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

test: all
	@./test.sh

test_overflow: all
	$(CC) $(G_ADDRESS_FLAGS) -o $@ $(OBJS) $(LIBRARIES)

norm:
	norminette */*.c */*.h

funcs:
	nm -u minishell | \
	grep -v "\(readline\|rl_clear_history\|rl_on_new_line\|rl_replace_line\| \
	rl_redisplay\|	add_history\|printf\|malloc\|free\|write\|access\|open\| \
	read\|close\|fork\|wait\|waitpid\|wait3\|wait4\|signal\|sigaction\| \
	sigemptyset\|sigaddset\|kill\|exit\|getcwd\|chdir\|stat\|lstat\|fstat\| \
	unlink\|execve\|dup\|dup2\|pipe\|opendir\|readdir\|closedir\|strerror\| \
	perror\|isatty\|ttyname\|ttyslot\|ioctl\|getenv\|tcsetattr\|tcgetattr\| \
	tgetent\|tgetflag\|tgetnum\|tgetstr\|tgoto\|tputs\)" | \
	grep -v '\w\+\s_\w\+'

.PHONY: all clean fclean re bonus test libft test_overflow

#########################
# Platform Compatibilty #
#########################

OS := $(shell uname -s)

ifeq ($(OS), linux)
	# linux command
endif

ifeq ($(OS), Darwin)
	READLINE_DIR = $(shell brew --prefix readline)
	INCLUDES += -I$(READLINE_DIR)/include
	LIBRARIES += -L$(READLINE_DIR)/lib
endif
