#ifndef GETCWD_H
# define GETCWD_H

#include "err_func.h"
#include "path_alloc.h"
#include <unistd.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <limits.h>

// err_func.c
void	err_sys(const char *fmt, ...);
void	err_ret(const char *fmt, ...);
void	err_quit(const char *fmt, ...);
void	err_dump(const char *fmt, ...);

// path_alloc.c
char	*path_alloc(size_t *sizep);

#endif
