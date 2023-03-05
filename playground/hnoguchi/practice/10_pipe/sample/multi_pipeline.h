/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipeline.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:52:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/22 11:10:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_PIPELINE_H
# define MULTI_PIPELINE_H

/*
 * Create muliti pipeline
 * ~$ cat pipeline.c | grep "a" | wc -l
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

# define BUF_SIZE 480

typedef struct s_pipe_fd t_pipe_fd;

typedef struct s_pipe_fd {
	char		**argv;
	int			pipe_fd[2];
	// int			file_fd;
	// char		*stashed_file_name;
	// int			stashed_file_fd;
	t_pipe_fd	*next;
}	t_pipe_fd;

void		fatal_error(char *location, char *message);
int			my_cat(char **read_str, int pipe_fd);
char		**create_argv(char *command);
t_pipe_fd	*create_pipe_fd_list(int size, char **argv);
void		frees_argv(char **argv);
void		frees_list(t_pipe_fd **list);
// chack
void		print_result_argv(char **argv);
void		print_result_list(t_pipe_fd **list);
void		print_result_execve(int fd);

# endif
