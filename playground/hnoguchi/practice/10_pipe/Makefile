#############
# Variables #
#############

NAME = pipeline
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LIBRARIES = -lreadline -lhistory
G_ADDRESS_FLAGS = -g -fsanitize=address
SRCS = main.c error_func.c is_func.c tokenize.c new_token.c \
	   parse.c redirect.c expand.c search_path.c pipe.c interpret.c \
	   destructor.c \
	   print_result.c print_result_redirect.c print_result_pipe.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))
OBJS_DIR = ./objs

#################
# General Rules #
#################

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBRARIES)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) overflow

re: fclean all

test: all
	@./test.sh

overflow: re
	$(CC) $(G_ADDRESS_FLAGS) -o $@ $(OBJS) $(LIBRARIES)


.PHONY: all clean fclean re test overflow

#########################
# Platform Compatibilty #
#########################

OS := $(shell uname -s)

ifeq ($(OS), linux)
	# linux command
endif

ifeq ($(OS), Darwin)
	READLINE_DIR = $(shell brew --prefix readline)
	INCLUDES = -I$(READLINE_DIR)/include
	LIBRARIES += -L$(READLINE_DIR)/lib
endif
