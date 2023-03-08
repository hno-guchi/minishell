#############
# Variables #
#############

NAME_1 = signal
NAME_2 = redisplay
NAME_3 = on_new_line
NAME_4 = clear_history
NAME_5 = replace_line
NAME_6 = rl_signal

CC = cc
G_FLAGS = -Wall -Wextra -Werror
G_SANITIZE = -g -fsanitize=address
LIBRARIES = -lreadline -lhistory

#################
# General Rules #
#################

.PHONY: $(NAME_1) $(NAME_2) $(NAME_3) $(NAME_4) $(NAME_5) $(NAME_6)

$(NAME_1):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) signal.c $(LIBRARIES)

$(NAME_2):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) rl_redisplay.c $(LIBRARIES)

$(NAME_3):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) rl_on_new_line.c $(LIBRARIES)

$(NAME_4):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) rl_clear_history.c $(LIBRARIES)

$(NAME_5):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) rl_replace_line.c $(LIBRARIES)

$(NAME_6):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) rl_signal.c $(LIBRARIES)

fclean:
	$(RM) $(NAME_1)
	$(RM) $(NAME_2)
	$(RM) $(NAME_3)
	$(RM) $(NAME_4)
	$(RM) $(NAME_5)
	$(RM) -r $(NAME_1).dSYM
	$(RM) -r $(NAME_2).dSYM
	$(RM) -r $(NAME_3).dSYM
	$(RM) -r $(NAME_4).dSYM
	$(RM) -r $(NAME_5).dSYM

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
