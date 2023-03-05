#############
# Variables #
#############

NAME = append_out
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
G_ADDRESS_FLAGS = -g -fsanitize=address
SRCS = main.c error.c error_func.c is_func.c new_token.c \
	   tokenize.c parse.c expand.c redirect.c search_path.c interpret.c
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
