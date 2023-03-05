/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_callback_handler_remove.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:25 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/28 16:02:08 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// readline.info
/*
 * L. 1666 ~
 * - Variable: rl_voidfunc_t *rl_deprep_term_fnction
 *   If non-zero, Readline will call indirectly through this pointer to reset the terminal.
 *   This function should undo the effects of `rl_prep_term_function'.
 *   By default, this is set to `rl_deprep_terminal' (*note Terminal Management::).
 *
 * L. 1683 ~
 * - Variable: int rl_readline_state
 *   A variable with bit values that encapsulate the current Readline state.
 *   A bit is set with the `RL_SETSTATE' macro, and unset with the `RL_UNSETSTATE' macro.
 *   Use the `RL_ISSTATE' macro to test whether a particular state bit is set.
 *   Current state bits include:
 *
 * L. 2579 ~
 * The following functions install and remove Readline's signal handlers.
 *
 * - Function: int rl_clear_signals (void);
 *   Remove all of the Readline signal handlers installed by `rl_set_signals()'.
 *
*/

// readline.h
// L.456
READLINE_DLL_IMPEXP int	rl_clear_signals PARAMS((void));
// L.868
#define RL_UNSETSTATE(x)	(rl_readline_state &= ~(x))


// rlprivate.h
// L.41
#define RL_CHECK_SIGNALS() \
	do { \
		if (_rl_caught_signal) _rl_signal_handler (_rl_caught_signal); \
	} while (0)

// signals.c
// L.434
int	rl_clear_signals()
{
	sighandler_cxt	dummy;

	if (rl_catch_signals && signals_set_flag == 1)
    {
		sigemptyset (&dummy.sa_mask);
		rl_sigaction (SIGINT, &old_int, &dummy);
		rl_sigaction (SIGTERM, &old_term, &dummy);

#if defined (SIGQUIT)
		rl_sigaction (SIGQUIT, &old_quit, &dummy);
#endif

#if defined (SIGALRM)
		rl_sigaction (SIGALRM, &old_alrm, &dummy);
#endif

#if defined (SIGTSTP)
		rl_sigaction (SIGTSTP, &old_tstp, &dummy);
#endif /* SIGTSTP */

#if defined (SIGTTOU)
		rl_sigaction (SIGTTOU, &old_ttou, &dummy);
#endif /* SIGTTOU */

#if defined (SIGTTIN)
      rl_sigaction (SIGTTIN, &old_ttin, &dummy);
#endif /* SIGTTIN */

      signals_set_flag = 0;
    }

#if defined (SIGWINCH)
	if (rl_catch_sigwinch && sigwinch_set_flag == 1)
	{
		sigemptyset (&dummy.sa_mask);
		rl_sigaction (SIGWINCH, &old_winch, &dummy);
		sigwinch_set_flag = 0;
	}
#endif
  return 0;
}
#endif /* !_WIN32 */

// callback.c
// L. 69 terminal_prepped and signals set?
static int	in_handler;
/* Remove the handler, and make sure the terminal is in its normal state. */
void	rl_callback_handler_remove()
{
	rl_linefunc = NULL;
	RL_UNSETSTATE (RL_STATE_CALLBACK);
	RL_CHECK_SIGNALS ();
	if (in_handler)
	{
		in_handler = 0;
		if (rl_deprep_term_function)
		{
			(*rl_deprep_term_function) ();
		}
#if define (HANDLE_SIGNALS)
			rl_clear_signals();
#endif
	}
}
