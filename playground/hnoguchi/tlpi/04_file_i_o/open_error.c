/*
 * 『The Linux Programming Interface』p.77
 *
 * #include <sys/stat.h>
 * #include <fcntl.h>
 * int	open(const char *pathname, int flags, ... [mode_t mode] );
 * 4.3.2	Errors from open();
 * EACCESS：アクセスできないファイルを指定した場合に発生する
 * EISDIR ；pathnameにディレクトリを指定した場合に発生する
 * EMFILE ；プロセスが使用できるファイルディスクリプターの上限に達した場合に発生する
 * ENFILE ；システム全体が使用できるファイルディスクリプターの上限に達した場合に発生する
 * ENOENT ；pathnameに指定したファイルが存在しない。かつ O_CREATE flag を指定しない場合に発生する。
 * 			O_CREATE flag を指定するが、pathnameで指定したディレクトリが存在しなかった場合に発生する。
 * 			O_CREATE flag を指定するが、pathnameで指定したsymbolic link が存在しないpathnameを指している場合に発生する。
 * EROFS  ；読み込み専用のファイルに、書き込みとしてopenした場合に発生する。
 * ETXTBSY；実行中の実行ファイルをopenした場合に発生する。
 * 			また、関連する実行可能ファイルを変更することは、許可されていない。
 */

/*
 * ~$ ./a.out notfile
 * errno is [2]
 * open(): No such file or directory
 *
 * ~$ ./a.out [dir]
 * errno is [21]
 * open(): Is a directory
 *
 * ~$ ./a.out [read_only file]
 * errno is [13]
 * open(): Permission denied
 *
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	fd;

	fd = 0;
	if (argc != 2)
	{
		fd = open(argv[0], O_WRONLY);
		if (fd == -1)
		{
			dprintf(STDERR_FILENO, "errno is [%d]\n", errno);
			perror("open()");
			exit(1);
		}
	}
	else
	{
		fd = open(argv[1], O_WRONLY);
		if (fd == -1)
		{
			dprintf(STDERR_FILENO, "errno is [%d]\n", errno);
			perror("open()");
			exit(1);
		}
	}
	close(fd);
	dprintf(STDOUT_FILENO, "SUCEESS open();\n");
	exit(0);
}

