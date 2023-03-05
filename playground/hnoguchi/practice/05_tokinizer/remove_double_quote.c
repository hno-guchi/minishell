#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// エラーを報告する関数
// printfと同じ引数をとる
void	error(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

# define DOUBLE_QUOTE_CHAR '\"'

void	add_char(char **new_word, char c)
{
	size_t	size;
	char	*temp;

	size = 2;
	if (*new_word != NULL)
	{
		size += strlen(*new_word);
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			error("malloc");
		}
		strlcpy(temp, *new_word, size);
		free(*new_word);
	}
	else
	{
		temp = malloc(size * sizeof(char));
		if (temp == NULL)
		{
			error("malloc");
		}
	}
	temp[size - 2] = c;
	temp[size - 1] = '\0';
	*new_word = temp;
}

void	remove_double_quote(char *before_word)
{
	size_t	i;
	char	*new_word;

	i = 0;
	new_word = NULL;
	while (before_word[i] != '\0')
	{
		if (before_word[i] != DOUBLE_QUOTE_CHAR)
		{
			add_char(&new_word, before_word[i]);
		}
		i += 1;
	}
	printf("before : [%s]\n", before_word);
	printf("after  : [%s]\n", new_word);
	free(new_word);
}

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

// 'asd'
// as'df'
// asde''
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		error("Not argument...");
	}
	remove_double_quote(argv[1]);
	// system("leaks -q a.out");
	exit (0);	
}
