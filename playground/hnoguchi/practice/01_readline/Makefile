CC = cc
CFLAGS = -I $(shell brew --prefix readline)/include
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
G_ADDRESS_FLAGS = -g -fsanitize=address
READLINE_LIB = -lreadline

test:
	@$(CC) -o minishell readline.c $(READLINE_LIB)
	@./test.sh


readline:
	$(CC) -o minishell readline.c $(READLINE_LIB)

readline_address:
	$(CC) $(G_ADDRESS_FLAGS) readline.c $(READLINE_LIB)

rl_gets:
	$(CC) $(G_ADDRESS_FLAGS) rl_gets.c $(READLINE_LIB)

rl_clear_history:
	$(CC) $(CFLAGS) $(LDFLAGS) rl_clear_history.c

rl_on_new_line:
	$(CC) $(G_ADDRESS_FLAGS) $(CFLAGS) $(LDFLAGS) rl_on_new_line.c

rl_replace_line:
	$(CC) $(G_ADDRESS_FLAGS) $(CFLAGS) $(LDFLAGS) rl_replace_line.c

rl_redisplay:
	$(CC) $(G_ADDRESS_FLAGS) $(CFLAGS) $(LDFLAGS) rl_redisplay.c

alternate_interface:
	$(CC) $(G_ADDRESS_FLAGS) $(CFLAGS) $(LDFLAGS) alternate_interface_example.c
