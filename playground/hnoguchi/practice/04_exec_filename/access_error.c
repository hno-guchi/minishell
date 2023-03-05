/*
 * ERROR
 * path == NULL
 * return : Bad address (errno == 14)
 *
 * path == "";
 * return : No such file or directory (errno == 2)
 * 
 * path == [Not exe file]; mode == X_OK
 * return : Permission denied (errno == 13)
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int	set_mode(char *mode)
{
	if (strcmp(mode, "f") == 0)
	{
		return (F_OK);
	}
	if (strcmp(mode, "r") == 0)
	{
		return (R_OK);
	}
	if (strcmp(mode, "w") == 0)
	{
		return (W_OK);
	}
	return (X_OK);
}

int	main(int argc, char **argv)
{
	int	mode;

	mode = X_OK;
	if (argc == 3)
	{
		mode = set_mode(argv[2]);
		if (access(argv[1], mode) != 0)
		{
			dprintf(STDERR_FILENO, "errno == [%d]\n", errno);
			perror("access");
			strerror(errno);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (access(argv[1], mode) != 0)
		{
			dprintf(STDERR_FILENO, "errno == [%d]\n", errno);
			perror("access");
			strerror(errno);
			exit(EXIT_FAILURE);
		}
	}
	printf("[%s] is OK!\n", argv[1]);
	exit(EXIT_SUCCESS);
}
