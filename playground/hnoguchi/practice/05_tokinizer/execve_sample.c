#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	main(void)
{
	char		*argv[] = {"/bin/echo", "Hello", "world", NULL};
	extern char **environ;

	execve("/bin/echo", argv, environ);
	perror("execve");
	exit(errno);
}
