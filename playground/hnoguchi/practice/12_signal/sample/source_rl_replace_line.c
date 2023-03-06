/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_replace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:17:22 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/02/28 17:36:33 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/JuliaAttic/readline/blob/9e182c9a057c8f3eea14bf5dc13f047fbb260abd/text.c

// readline.info
// L.2266 ~
/*
 * Utility Functions
 * -----------------
 *
 *  - Function: void rl_replace_line (const char *text, int clear_undo)
 *    Replace the contents of `rl_line_buffer' with TEXT.
 *    The point and mark are preserved, if possible.
 *    If CLEAR_UNDO is non-zero, the undo list associated with the current line is cleared.
 */

// text.c
// L. 204 ~
/* Replace the current line buffer contents with TEXT.
 * If CLEAR_UNDO is non-zero, we free the current undo list.
 */
void	rl_replace_line(text, clear_undo)
	const char	text;
	int			clear_undo;
{
	int	len;

	len = strlen(text);
	if (len >= rl_line_buffer_len)
	{
		rl_extend_line_buffer(len);
	}
	strlcpy(rl_line_buffer, text);
	rl_end = len;

	if (clear_undo)
	{
		rl_free_undo_list();
	}
	_rl_fix_point(1);
}
