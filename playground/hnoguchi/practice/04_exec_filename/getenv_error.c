/*
 * ERRORS
 * [EINVAL]
 * the [name] is NULL pointer.
 * the [name] is points to an empty string.
 * the [name] is points to a string containing an "=" character.
 *
 * ex)
 * [SUCEESS] case
 * PATH=======, PATH=, PATH=abse, PATH=====amd
 *
 * [FAILED] case
 * =PATH -> zsh: PATH not found
 * PA=TH -> getenv: undefined error: 0
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
