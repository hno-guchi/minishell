#############
# Variables #
#############

LIBRARIES = -lreadline -lhistory

here_document:
	gcc  $(INCLUDES) here_document.c $(LIBRARIES)

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
