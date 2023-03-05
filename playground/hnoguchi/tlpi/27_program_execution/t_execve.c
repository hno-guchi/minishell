/*
 * #include <unistd.h>
 * int	exeve(const char *pathname, char const **argv, char const **envp);
 *
 * RETURN VALUE
 * [success]
 * never return.
 * [failed]
 * return -1.
 */

/*
 * Using execve(); to execute a new program
 */
#include <unistd.h>
#include "curr_time.h"
#include "tlpi_hdr.h"

int	main(int argc, char **argv)
{
	/* Larger than required */
	char	*argVec[10];
	// char	*envVec[] = {"GREET=salut", "BYE=adieu", NULL};
	extern char	**environ;

	if (argc != 2 || (strcmp(argv[1], "--help") == 0))
	{
		usageErr("%s pathname\n", argv[0]);
	}
	// Get basename from argv[1];
	argVec[0] = strrchr(argv[1], '/');
	if (argVec[0] != NULL)
	{
		argVec[0]++;
	}
	else
	{
		argVec[0] = argv[1];
	}
	argVec[1] = "Hello, world!";
	argVec[2] = "goodbye";
	// List must be NULL-terminated
	argVec[3] = NULL;

	execve(argv[1], argVec, environ);
	// If we get here, something went wrong.
	errExit("execve");
}
