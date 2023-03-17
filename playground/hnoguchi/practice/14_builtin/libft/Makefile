NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

ARFLAGS = rcs

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlen.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_calloc.c ft_strjoin.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_strdup.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
 		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_strclen.c ft_strcmp.c ft_strncpy.c ft_strndup.c

INCLUDES_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

INCLUDE = $(addprefix -I, ./$(INCLUDES_DIR))

OBJS = $(addprefix ./$(OBJS_DIR)/, $(SRCS:%.c=%.o))

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
