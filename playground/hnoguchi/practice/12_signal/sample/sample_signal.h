/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:14:11 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 14:44:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_SIGNAL_H
# define SAMPLE_SIGNAL_H


void	sigint_signal_receiver(void handler(int, siginfo_t *, void*));
void	sigint_signal_handler(int signal_number, siginfo_t *info, void *ucontext_ap);

#endif
