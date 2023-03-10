#include "add_2.h"

/*
 * 標準入出力バッファリングによって、デッドロックが起こる
 */

int	main(void)
{
	int		int_1;
	int		int_2;
	char	line[MAXLINE];

	/*
	if (setvbuf(stdin, NULL, _IOLBF, 0) != 0)
	{
		err_sys("setvbuf error");
	}
	if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
	{
		err_sys("setvbuf error");
	}
	*/
	while (fgets(line, MAXLINE, stdin) != NULL)
	{
		if (sscanf(line, "%d%d", &int_1, &int_2) == 2)
		{
			if (printf("%d\n", int_1 + int_2) == EOF)
			{
				err_sys("printf error");
			}
		}
		else
		{
			if (printf("invalid args\n") == EOF)
			{
				err_sys("printf error");
			}
		}
	}
	return (0);
}
