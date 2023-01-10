#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/* A static variable for holding the line. */
static char	*line_read = (char *)NULL;

/*
 * Read a string, and return a pointer to it.
 * Returns NULL on EOF.
 */
char	*rl_gets()
{
	/*
	 * If the buffer has already been alocated,
	 * return the memory to the free pool.
	 */
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	/*
	 * Get a line from the user.
	 */
	line_read = readline("minishell > ");
	/*
	 * If the line has any text in it,
	 * save it on the history.
	 */
	if (line_read && *line_read)
	{
		add_history(line_read);
	}
	return (line_read);
}

int	main()
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = rl_gets();
		printf("%s\n", line);
		// free(line);
	}
	printf("exit\n");
	return (0);
}
