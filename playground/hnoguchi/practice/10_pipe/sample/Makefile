#############
# Variables #
#############

G_FLAGS = -Wall -Wextra -Werror
G_SANITIZE = -g -fsanitize=address
LIBRARIES = -lreadline -lhistory

#################
# General Rules #
#################

.PHONY: here_document multi_pipeline clean_redirects fclean sanitize_address

here_document:
	gcc  $(INCLUDES) here_document.c $(LIBRARIES)

multi_pipeline:
	gcc -o $@ $(G_FLAGS) multi_pipeline.c pipeline_func.c

sanitize_address:
	gcc -o $@ $(G_SANITIZE) multi_pipeline.c pipeline_func.c

clean_redirects:
	$(RM) f1 f2 f3

fclean:
	$(RM) a.out
	$(RM) multi_pipeline
	$(RM) here_document
	$(RM) sanitize_address

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
