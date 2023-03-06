/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:11:11 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/06 16:10:28 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

// signal.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <unistd.h>
#include <signal.h>

/*
 * man sigemptyset
 * #include <signal.h>
 *
 * int	sigemptyset(sigset_t *set);
 *
 * These functions manipulate signal sets, stored in a sigset_t.
 * Either sigemptyset(); or sigfillset(); must be called for every object of type sigset_t before any other use of the object.
 * The function initializes a signal set to be empty.
 * struct	sigaction {
 * 				union __sigaction_u __sigaction_u;	// signal handler
 * 				sigset_t			sa_mask;		// signal mask to apply
 * 				int					sa_flags;		// see signal options below
 * 				};
 *
 * man sigaction
 * Options may be specified by setting sa_flags.
 * The meaning of the various bits is as follows:
 *
 * SA_SIGINFO
 * If this bit is set,
 * the handler function is assumed to be pointed to by the sa_sigaction member of struct sigaction
 * and should match the prototype shown above or as below in EXAMPLES.
 * This bit should not be set when assigning SIG_DFL or SIG_IGN.
 */

void	fatal_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

void	signal_quit_handler(int signal_number)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) < 0)
	{
		fatal_error("sigaction");
	}
	if (sigaction(signal_number, &sa, NULL) < 0)
	{
		fatal_error("sigaction");
	}
}

void	sa_initialize(int signal_number, struct sigaction *sa)
{
	if (sigemptyset(&sa->sa_mask) < -1)
	{
		fatal_error("sigemptyset");
	}
	if (sigaction(signal_number, sa, NULL) < -1)
	{
		fatal_error("sigaction");
	}
}

void	signal_int_handler(int signal_number, siginfo_t *info, void *ucontext_ap)
{
	(void)info;
	(void)ucontext_ap;
	if (signal_number == SIGINT)
	{
		write(STDOUT_FILENO, "catch SIGINT\n", 13);
	}
}

void	signal_receiver(int signal_number, void handler(int, siginfo_t *, void*))
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sa_initialize(signal_number, &sa);
}

int	main(void)
{
	char	*line;

	signal_receiver(SIGINT, signal_int_handler);
	signal(SIGQUIT, signal_quit_handler);

	line = NULL;
	while(1)
	{
		line = readline("signal$ ");
		if (line == NULL)
		{
			break ;
		}
		if (0 < strlen(line))
		{
			add_history(line);
		}
		free(line);
	}
	exit (EXIT_SUCCESS);
}
