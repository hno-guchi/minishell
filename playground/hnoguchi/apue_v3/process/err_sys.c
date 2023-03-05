#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 4096

static void	err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	if (errnoflag)
	{
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
	}
	strcat(buf, "\n");
	/* stroutとstderrが同じ場合 */
	fflush(stdout);
	fputs(buf, stderr);
	/* すべての標準出力ストリームをフラッシュ */
	fflush(NULL);
}

/*
 * システムコール関連の致命的エラー
 * メッセージを表示して終了
 */
void	err_sys(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}
