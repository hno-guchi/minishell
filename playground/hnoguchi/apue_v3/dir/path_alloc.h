#ifndef PATH_ALLOC_H
# define PATH_ALLOC_H

#ifdef PATH_MAX
static long	pathmax = PATH_MAX;
#else
static long	pathmax = 0;
#endif

#include "err_func.h"
#include <unistd.h>
#include <errno.h>
#include <limits.h>

static long	posix_version = 0;
static long	xsi_version = 0;

/* PATH_MAX が不定の時、これが適切である保証はない */
#define PATH_MAX_GUESS 1024

// error_func.c
void	err_sys(const char *fmt, ...);

#endif
