#ifndef POPEN_H
# define POPEN_H

#include "err_func.h"
// #include <unistd.h>
#include <stdio.h>
// #include <sys/wait.h>

/* デフォルトのペイジェープログラム */
# define DEF_PAGER "/bin/more"

// err_func.c
void	err_sys(const char *fmt, ...);
void	err_ret(const char *fmt, ...);
void	err_quit(const char *fmt, ...);
void	err_dump(const char *fmt, ...);

#endif
