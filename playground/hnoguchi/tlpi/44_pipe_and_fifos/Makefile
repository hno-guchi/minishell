simple_pipe:
	gcc -o $@ -I../03_system_programming_concepts \
		../03_system_programming_concepts/error_functions.c \
		simple_pipe.c

pipe_sync:
	gcc -o $@ -I../03_system_programming_concepts \
		-I../10_time \
		../03_system_programming_concepts/error_functions.c \
		../03_system_programming_concepts/get_num.c \
		../10_time/curr_time.c \
		pipe_sync.c
pipe_ls_wc:
	gcc -o $@ -I../03_system_programming_concepts \
		../03_system_programming_concepts/error_functions.c \
		pipe_ls_wc.c

fclean:
	$(RM) simple_pipe pipe_sync pipe_ls_wc
