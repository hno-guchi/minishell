#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * https://tiswww.case.edu/php/chet/readline/readline.html#Readline-Convenience-Functions
 * void	rl_clear_history(void);
 * Clear the history list by deleting all of the entries,
 * in the same manner as the History library's clear_history(); function.
 * This differs from clear_history(); because it frees private data Readline saves in the history list.
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
			rl_clear_history();
			printf("[Clear history]\n");
			continue ;
			// free(line);
			// break ;
		}
		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
