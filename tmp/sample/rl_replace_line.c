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
 * void	rl_replace_line(const char *text, int clear_undo);
 * Replace the contents of [rl_line_buffer] with text.
 * The point and mark are preserved, if possible.
 * If clear_undo is non-zero, the undo list associated with the current line is cleared.
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
			rl_replace_line("", 0);
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
