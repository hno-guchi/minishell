/*
 * #include <stdlib.h>
 * char	*getenv(const char *name);
 * 
 * environment variable function
 *
 * RETURN VALUES
 * [exist name]
 * the value of the environment variable as a NUL-terminated string.
 * [not exist name]
 * Return NULL.
 *
 * ERRORS
 * [EINVAL]
 * the [name] is NULL pointer, points to an empty string,
 * or points to a string containing an "=" character.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	char	*env_value;

	if (argc == 2)
	{
		env_value = getenv(argv[1]);
	}
	else
	{
		env_value = getenv(NULL);
	}

	if (env_value == NULL)
	{
		perror("getenv");
		dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		exit (EXIT_FAILURE);
	}
	printf("%s = %s\n", argv[1], env_value);
	exit(0);
}
