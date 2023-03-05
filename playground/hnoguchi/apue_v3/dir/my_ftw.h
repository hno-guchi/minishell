#ifndef MY_FTW_H
# define MY_FTW_H

#include "err_func.h"
#include "path_alloc.h"
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

/* 各ファイル名毎に呼び出す関数の型 */
typedef int	Myfunc(const char *, const struct stat *, int);
static Myfunc	myfunc;

#define FTW_F 1		/* dir以外のファイル */
#define FTW_D 2		/* dir */
#define FTW_DNR 3	/* 読めないdir */
#define FTW_NS 4	/* statを取得できないファイル */

/* 各ファイルの完全パス名 */
static char		*fullpath;
static size_t	pathlen;
static long		nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;



// err_func.c
void	err_sys(const char *fmt, ...);
void	err_ret(const char *fmt, ...);
void	err_quit(const char *fmt, ...);
void	err_dump(const char *fmt, ...);



// path_alloc.c
char	*path_alloc(size_t *sizep);

#endif
