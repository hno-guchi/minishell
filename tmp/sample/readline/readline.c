#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * char	*readline(const char *prompt);
 */

int	main()
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("line is [%s]\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
