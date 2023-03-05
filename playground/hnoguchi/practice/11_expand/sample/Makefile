#############
# Variables #
#############

NAME_1 = variable
NAME_2 = expand
NAME_3 = special_param

CC = cc
G_FLAGS = -Wall -Wextra -Werror
G_SANITIZE = -g -fsanitize=address
LIBRARIES = -lreadline -lhistory

#################
# General Rules #
#################

.PHONY: $(NAME_1) $(NAME_2) $(NAME_3)

$(NAME_1):
	$(CC) -o $@ $(G_FLAGS) variable.c
	# $(CC) -o $@ $(G_SANITIZE) only_getenv.c

$(NAME_2):
	# $(CC) -o $@ $(G_FLAGS) variable.c expand.c
	$(CC) -o $@ $(G_SANITIZE) variable.c special_param.c expand.c

$(NAME_3):
	$(CC) -o $@ $(G_FLAGS) special_param.c
	# $(CC) -o $@ $(G_SANITIZE) variable.c expand.c

fclean:
	$(RM) $(NAME_1)
	$(RM) $(NAME_2)
	$(RM) $(NAME_3)
	$(RM) -r $(NAME_1).dSYM
	$(RM) -r $(NAME_2).dSYM
	$(RM) -r $(NAME_3).dSYM

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
