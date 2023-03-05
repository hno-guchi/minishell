/*
 * https://tiswww.case.edu/php/chet/readline/readline.html#Readline-Convenience-Functions
 *
 * Variable char	*rl_line_buffer;
 * This is the line gathered so far.
 * You are welcome to modify the contents of the line, but see section Allowing Undoing.
 *
 *
 *
 * void	rl_replace_line(const char *text, int clear_undo);
 * Replace the contents of [rl_line_buffer] with text.
 * The point and mark are preserved, if possible.
 * If clear_undo is non-zero, the undo list associated with the current line is cleared.
 *
 *
 *
 * int	rl_on_new_line(void);
 * Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
 *
 *
 *
 * int	rl_redisplay();
 * Change what's displayed on the screen to reflect the current contents of [rl_line_buffer].
 *
 *
 */

/*
catch_signal_ctrl_c()
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
*/


