/*
 * #include <unistd.h>
 * int	pipe(int fildes[2]);
 *
 * Create descriptor pair for interprocess communication
 *
 * DESCRIPTION
 * The function creates a pipe.
 * Pipe is an object that allows unidirectional data flow and allocates a pair of file descriptors.
 * fildes[0]; connects to the read end of the pipe.
 * fildes[1]; connects to the write end.
 *
 * Data written to fildes[1]; appears on fildes[0];.
 * This allows the output of one program to be sent to another program.
 * The source's standard output is set up to be the write end of the pipe.
 * The sink's standard input is set up to be the read end of the pipe.
 * the pipe itself persists until all of its associated descriptors are closed.
 * A pipe whose read or write end has been closed is considered widowed.
 * Writing on such a pipe causes the writing process to receive a SIGPIPE signal.
 *
 * RETURN VALUES
 * Success 0 returned.
 * Otherwise -1 returned and set [errno].
 *
 * [The Linux Programming Interface]
 * 44. PIPES AND FIFOS
 *  1. Overview
 *
 * p. 899 ~
 * 
 *
 */

