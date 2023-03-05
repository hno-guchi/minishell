#ifndef MAIN_H
# define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	err_ret(const char *fmt, ...);
void	err_sys(const char *fmt, ...);

#endif
