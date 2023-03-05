/*
 * #include <unistd.h>
 * int	access(const char *path, int mode);
 *
 * check accessibility of a file
 */
#include "err_func.h"
#include <unistd.h>
#include <fcntl.h>

/*
 * 関数accessの使用例
 * 引数に与えられたファイルのアクセス検査（R_OK:読み取り可能か）調べる
 */
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		err_quit("Usage: a.out <pathname>");
	}
	
	if (access(argv[1], R_OK) < 0)
	{
		err_ret("access error for %s", argv[1]);
	}
	else
	{
		printf("read access OK\n");
	}

	if (open(argv[1], O_RDONLY) < 0)
	{
		err_ret("open error for %s", argv[1]);
	}
	else
	{
		printf("open for reading OK\n");
	}
	exit(0);
}
