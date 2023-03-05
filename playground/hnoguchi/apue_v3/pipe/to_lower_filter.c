/*
 * 大文字を小文字に変換するフィルタ
 */

#include "to_lower_filter.h"

int	main(void)
{
	int	c;

	while ((c = getchar()) != EOF)
	{
		if (isupper(c))
		{
			c = tolower(c);
		}
		if (putchar(c) == EOF)
		{
			err_sys("output error");
		}
		if (c == '\n')
		{
			fflush(stdout);
		}
	}
	return (0);
}
