#include "add_2.h"

int	main(void)
{
	int		n;
	int		int_1;
	int		int_2;
	char	line[MAXLINE];

	while (0 < (n = read(STDIN_FILENO, line, MAXLINE)))
	{
		/* 終端のnull */
		line[n] = 0;
		if (sscanf(line, "%d%d", &int_1, &int_2) == 2)
		{
			sprintf(line, "%d\n", int_1 + int_2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
			{
				err_sys("write error");
			}
		}
		else
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
			{
				err_sys("write error");
			}
		}
	}
	return (0);
}
