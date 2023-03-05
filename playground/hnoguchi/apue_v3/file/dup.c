/*
 * #include <unistd.h>
 * int	dup(int fildes);
 * int	dup2(int fildes, int fildes2);
 *
 * duplicate an existing file descriptor
 *
 * DESCRIPTION
 * dup() duplicates an existing object descriptor and returns its value to the calling process (fildes2 = dup(fildes)).
 * The argument [fildes] is a small non-negative integer index in the per-process descriptor table.
 *
 * */
