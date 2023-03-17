#############
# Variables #
#############

NAME = minishell
CC = cc
INCLUDES = -I./includes -I./libft/includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LIBRARIES = -lreadline -lhistory -lft -L./libft
G_ADDRESS_FLAGS = -g -fsanitize=address
SRCS = main.c

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
