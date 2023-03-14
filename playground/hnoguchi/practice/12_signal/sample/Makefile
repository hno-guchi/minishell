#############
# Variables #
#############

NAME_1 = signal
NAME_2 = redisplay
NAME_3 = on_new_line
NAME_4 = clear_history
NAME_5 = replace_line
NAME_6 = rl_signal
NAME_7 = sigint_in_heredoc
NAME_8 = sigint_in_single_blocking
NAME_9 = sigint_in_multi_blocking

CC = cc
G_FLAGS = -Wall -Wextra -Werror
G_SANITIZE = -g -fsanitize=address
LIBRARIES = -lreadline -lhistory

#################
# General Rules #
#################

.PHONY: $(NAME_1) $(NAME_2) $(NAME_3) $(NAME_4) $(NAME_5) $(NAME_6) $(NAME_7) $(NAME_8) $(NAME_9)

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
$(NAME_7):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) sigint_in_here_document.c $(LIBRARIES)
$(NAME_8):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) sigint_in_single_blocking.c $(LIBRARIES)
$(NAME_9):
	$(CC) -o $@ $(G_FLAGS) $(INCLUDES) sigint_in_multi_blocking.c $(LIBRARIES)

fclean:
	$(RM) $(NAME_1) $(NAME_2) $(NAME_3) $(NAME_4) $(NAME_5) $(NAME_6) $(NAME_7) $(NAME_8) $(NAME_9)
	$(RM) -r $(NAME_1).dSYM $(NAME_2).dSYM $(NAME_3).dSYM $(NAME_4).dSYM $(NAME_5).dSYM $(NAME_6).dSYM $(NAME_7).dSYM $(NAME_8).dSYM $(NAME_9).dSYM

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
