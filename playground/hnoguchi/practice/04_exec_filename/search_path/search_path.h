/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:58:37 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/01 11:58:51 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_PATH_H
# define SEARCH_PATH_H

#include <unistd.h>
// #include <ctype.h>
#include <stdarg.h>
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

# define SIZE_OPERATORS_LIST 9
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define END "\x1b[39m"

// error.c
void	error(char *fmt, ...);
void	fatal_error(char *fmt, ...);
void	error_message(const char *location, const char *message, int status);

// interpret.c
int	interpret(char **argv);

// search_path.c
char	*search_path(const char *file_name);

# endif
