/*
 * #include <unistd.h>
 * char	*getcwd(char *buf, size_t size);
 *
 * get working directory pathname
 *
 * getcwd()の使用例
 */

#include "getcwd.h"

int	main(void)
{
	char	*ptr;
	size_t	size;

	if (chdir("/usr/local") < 0)
	{
		err_sys("chdir failed");
	}
	ptr = path_alloc(&size);
	if (getcwd(ptr, size) == NULL)
	{
		err_sys("getcwd failed");
	}
	printf("cwd = %s\n", ptr);
	exit(0);
}
