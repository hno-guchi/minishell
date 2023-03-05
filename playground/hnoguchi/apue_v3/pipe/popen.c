/*
 * #include <stdio.h>
 * FILE	*popen(const char *command, const char *mode);
 * int	pclose(FILE *stream);
 *
 * process I/O
 *
 * sample.c をpopenを使って書き直したもの。
 */

#include "popen.h"

/* 環境変数、また、デフォルト */
#define PAGER "${PAGER:-more}"

int	main(int argc, char **argv)
{
	char	line[MAXLINE];
	FILE	*fpin;
	FILE	*fpout;

	if (argc != 2)
	{
		err_quit("usage: a.out <pathname>");
	}
	if ((fpin = fopen(argv[1], "r")) == NULL)
	{
		err_sys("can't open %s", argv[1]);
	}
	if ((fpout = popen(PAGER, "w")) == NULL)
	{
		err_sys("popen error");
	}
	/* argv[1]をPAGERへコピー */
	while (fgets(line, MAXLINE, fpin) != NULL)
	{
		if (fputs(line, fpout) == EOF)
		{
			err_sys("fputs error to pipe");
		}
	}
	if (ferror(fpin))
	{
		err_sys("fgets error");
	}
	if (pclose(fpout) == -1)
	{
		err_sys("pclose error");
	}
	return (0);
}
