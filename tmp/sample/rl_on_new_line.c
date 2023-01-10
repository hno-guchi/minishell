#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * https://tiswww.case.edu/php/chet/readline/readline.html#Readline-Convenience-Functions
 *
 * Variable char	*rl_line_buffer;
 * This is the line gathered so far.
 * You are welcome to modify the contents of the line, but see section Allowing Undoing.
 *
 *
 *
 * int	rl_on_new_line(void);
 * Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
 *
 */

int	main()
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (line == NULL || strlen(line) == 0)
		{
			rl_on_new_line();
			continue ;
		}
		else
		{
			printf("%s\n", line);
		}
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
