/*
 * 『詳解　UNIXプログラミング　第３版』
 */
#include "err_func.h"

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
 * システムコール関連の非致命的エラー
 * メッセージを表示して戻る
 */
void	err_ret(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
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

/*
 * システムコールに関連しない致命的なエラー
 * メッセージを表示して終了。
 */
void	err_quit(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * システムコール関連の致命的エラー
 * メッセージを表示し、コアダンプして終了。
 */
void	err_dump(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	/* コアダンプして終了 */
	abort();
	/* exit(1)には来ないはず */
	exit(1);
}

/*
 * メッセージを表示して戻る。
 */
void	err_msg(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}
