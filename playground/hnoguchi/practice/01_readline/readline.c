#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * #include <stdio.h>
 * #include <readline/readline.h>
 * #include <readline/history.h>
 * char	*readline(const char *prompt);
 *
 * get a line from a user with editing.
 *
 * RETURN VALUE
 * . the text of the line read.
 * . the empty string. -> About a blank line.
 * . NULL. -> About EOF is encountered while reading a line, and the line is empty.
 *   (if an EOF is read with non-empty line, it is treated as a newline)
 */

int	main(void)
{
	char	*line;

	line = NULL;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			// printf("\n");
			break ;
		}
		if (strlen(line))
		{
			add_history(line);
		}
		// TODO: intepret line as a command.
		free(line);
	}
	// printf("exit\n");
	// system("leaks -q a.out");
	exit (0);
}
