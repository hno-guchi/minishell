#include "path_alloc.h"

/* 非NULLの場合は、確保したサイズを返す */
char	*path_alloc(size_t *sizep)
{
	char	*ptr;
	size_t	size;

	if (posix_version == 0)
	{
		posix_version = sysconf(_SC_VERSION);
	}
	if (xsi_version == 0)
	{
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	}
	/* 初回 */
	if (pathmax == 0)
	{
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
		{
			if (errno == 0)
			{
				/* 不定 */
				pathmax = PATH_MAX_GUESS;
			}
			else
			{
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}
		else
		{
			/* ルート相対なので１を加える */
			pathmax += 1;
		}
	}
	/*
	 * POSIX.1-2001より前では、PATH＿MAXに終端のNULLバイトが含まれる保証はない。
	 * XPG3でも同様
	 */
	if ((posix_version < 200112L) && (xsi_version < 4))
	{
		size = pathmax + 1;
	}
	else
	{
		size = pathmax;
	}
	
	if ((ptr = malloc(size)) == NULL)
	{
		err_sys("malloc error for pathname");
	}
	if (sizep != NULL)
	{
		*sizep = size;
	}
	return (ptr);
}
