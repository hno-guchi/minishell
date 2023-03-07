/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_atty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:39:42 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/07 11:31:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * #include <unistd.h>
 *
 * int	isatty(int fd);
 * get name of associated terminal (tty) from file descriptor.
 *
 * These function operate on file descriptors for terminal type device.
 * The function determines if the file descriptor [fd] refers to a valid terminal type device.
 *
 * RETURN VALUES
 * Return 1 if fd refers to a terminal type device.
 * Otherwise, if returns 0 and may set [errno].
 *
 *
 */
