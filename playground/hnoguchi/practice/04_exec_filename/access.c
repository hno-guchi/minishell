/*
 * #include <unistd.h>
 * int	access(const char *path, int mode);
 *
 * check accessibility of a file
 *
 * RETURN VALUE
 * [success]
 * 0
 * [failed]
 * -1, and set errno
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) != 0)
	{
		perror("access(F_OK)");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) != 0)
	{
		perror("access(R_OK)");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], W_OK) != 0)
	{
		perror("access(W_OK)");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], X_OK) != 0)
	{
		perror("access(X_OK)");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	printf("[%s] is all OK!\n", argv[1]);
	exit(EXIT_SUCCESS);
}
