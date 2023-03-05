/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:11:00 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/09 10:33:27 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

#include <unistd.h>
#include <fcntl.h>
#include "parse.h"
#include "tokenize.h"


char	*search_path(const char *file_name);
int	interpret(t_token *token);

// parse.c
t_node	*parse(t_token *token);

// error_func.c
void	error_message(const char *location, const char *message, int status);

// redirect.c
void	redirect(t_node *node);
void	reset_redirect(t_node *node);

#endif
