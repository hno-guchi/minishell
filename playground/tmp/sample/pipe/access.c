/*
 * Check accessibility of a file.
 *
 * SYNOPSIS
 * #include <unistd.h>
 * int	access(const char *path, int mode);
 *
 * DESCRIPTION
 * The system call checks the accessibility of the file named by the [path] argument for the access permissions indicated by the [mode] argument.
 * The value of [mode] is either the bitwize-inclusive
 * OR of the access permission to be checked (
 * R_OK for read permission,
 * W_OK for write permission, and
 * X_OK for execute/search permission),
 * or the existence test (F_OK).
 *
 * The system call uses the real user ID in place of the effective user ID,
 * the real group ID in place of the effective group ID,
 * and the rest of the group access list.
 *
 * RETURN VALUES
 * About the value 0 is returned is success.
 * About the value -1 is returned and set errno is other than success.
 * */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	(void)argc;

	if (access(argv[1], R_OK) < 0)
	{
		printf("Access error for %s\n", argv[1]);
	}
	else
	{
		printf("Read access [OK]\n");
	}
	if (open(argv[1], O_RDONLY) < 0)
	{
		printf("Open error for %s\n", argv[1]);
	}
	else
	{
		printf("Open for reading [OK]\n");
	}
	return (0);
}
