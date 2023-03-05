#ifndef TLPI_HDR_H
# define TLPI_HDR_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "get_num.h"
#include "error_functions.h"

# define min(m, n) ((m) < (n) ? (m) : (n))
# define max(m, n) ((n) < (m) ? (m) : (n))

typedef enum {
	FALSE,
	TRUE
}	Boolean;

#endif
