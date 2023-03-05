#ifndef READ_COMMAND_H
# define READ_COMMAND_H

#include "err_func.h"
#include <ctype.h>
#include <sys/wait.h>

// err_func.c
void	err_sys(const char *fmt, ...);
void	err_ret(const char *fmt, ...);
void	err_quit(const char *fmt, ...);
void	err_dump(const char *fmt, ...);

#endif
