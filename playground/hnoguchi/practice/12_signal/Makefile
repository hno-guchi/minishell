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
	   error_func.c xperror.c \
	   initialize_sa.c initialize_signals.c set_signals_default.c set_signals_ignore.c set_signals_receiver.c \
	   destructor.c \
	   tokenize.c new_token.c new_token_type_word.c new_token_type_operator.c\
	   expand.c is_func.c add_character.c try_remove_quote.c append_func.c \
	   parse.c new_node.c at_eof.c list_add_back.c append_args.c append_redirects.c try_append_redirect.c \
	   redirect.c stash_fd.c open_redir_file.c read_here_document.c closes_redirect_file.c reset_redirect_command.c \
	   pipe.c \
	   interpret.c search_path.c exec_pipeline.c
		# sa_initialize.c check_signal.c reset_signal_handler.c
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
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

test: all
	@./test.sh

test_overflow: all
	$(CC) $(G_ADDRESS_FLAGS) -o $@ $(OBJS) $(LIBRARIES)

.PHONY: all clean fclean re bonus test libft

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
