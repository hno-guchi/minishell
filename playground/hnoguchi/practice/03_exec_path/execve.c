/*
 * #include <unistd.h>
 * int	execve(const char *path, char *const argv[], char *const envp[]);
 *
 * execute a file
 * 
 * DESCRIPTION
 * [path]
 * is called the [new process file].
 * This file is either an executable object file, or a file of data for an interpreter.
 *
 * [argv]
 * A pointer to a null-terminated array of character pointers
 * to null-terminated character strings.
 * These strings construct the argument must be present in the array;
 * by custom, the first element should be the name of the executed program.
 * (for example, the last component of [path])
 * 
 * [envp]
 * A pointer to same as [argv].
 * A pointer to this array is normally stored in the global variable [environ].
 * These strings pass information to the new process that is not directly an argument to the command.
 *
 * RETURN VALUES
 * [SUCCESS]
 * Not return
 * As the function overlays the current process image with a new process image, the successful call has no process to return to.
 *
 * CAVEAT
 * 実ユーザIDがrootの場合、スーパーユーザと同様の権限を持つ。
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	char	*arg_vec[10];
	char	*env_vec[] = {"GREET=salut", "BYE=adieu", NULL};

	if (argc != 2 || (strcmp(argv[1], "--help") == 0))
	{
		perror("pathname");
		exit(EXIT_FAILURE);
	}
	arg_vec[0] = strrchr(argv[1], '/');
	if (arg_vec[0] != NULL)
	{
		arg_vec[0]++;
	}
	else
	{
		arg_vec[0] = argv[1];
	}
	arg_vec[1] = "Hello, world";
	arg_vec[2] = "goodbye";
	arg_vec[3] = NULL;
	execve(argv[1], arg_vec, env_vec);
	perror("execve");
	exit(errno);
}
