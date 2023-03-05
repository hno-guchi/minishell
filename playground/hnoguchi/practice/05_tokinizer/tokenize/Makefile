#############
# Variables #
#############

NAME = tokenize
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
G_ADDRESS_FLAGS = -g -fsanitize=address
SRCS = main.c error.c is_func.c new_token.c tokenize.c
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

re: fclean all

test: all
	@./test.sh

.PHONY: all clean fclean re test
