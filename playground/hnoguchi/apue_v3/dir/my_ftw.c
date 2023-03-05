/*
 * #include <dirent.h>
 * DIR				*opendir(const char *filename);
 * struct dirent	*readdir(DIR *dirp);
 * int				closedir(DIR *dirp);
 *
 * directory operations
 */

/*
 * 自作ftw関数の作成
 * ファイル階層を辿るプログラム
 */
#include "my_ftw.h"

/*
 * "fullpath"から始めて階層構造を辿る
 * "fullpath"がディレクトリ以外であれば、lstat()を適用し、func()を呼んで戻る。
 * ディレクトリに対しては、ディレクトリ内の各名前に対して自身を再帰呼び出し。
 *
 * func()の戻り値を返す
 */
static int	dopath(Myfunc *func)
{
	struct stat		statbuf;
	struct dirent	*dirp;
	DIR				*dp;
	int				ret;
	int				n;

	/* stat error */
	if (lstat(fullpath, &statbuf) < 0)
	{
		return (func(fullpath, &statbuf, FTW_NS));
	}
	/* ディレクトリではない */
	if (S_ISDIR(statbuf.st_mode) == 0)
	{
		return (func(fullpath, &statbuf, FTW_F));
	}

	/*
	 * ディレクトリ。
	 * まず、func();を呼び、ディレクトリ内の各ファイルを処理。
	 */
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
	{
		return (ret);
	}
	n = strlen(fullpath);
	if (pathlen < (n + NAME_MAX + 2))
	{
		/* path bufを拡張 */
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
		{
			err_sys("realloc failed");
		}
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;
	if ((dp = opendir(fullpath)) == NULL)
	{
		/* 読めないディレクトリ */
		return (func(fullpath, &statbuf, FTW_DNR));
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		if (strcmp(dirp->d_name, ".") == 0
				|| strcmp(dirp->d_name, "..") == 0)
		{
			/* ".", ".." dirは無視 */
			continue ;
		}
		/* 名前の末尾に"/" を追加 */
		strcpy(&fullpath[n], dirp->d_name);
		/* 再帰呼び出し */
		if ((ret = dopath(func)) != 0)
		{
			/* 戻る */
			break ;
		}
	}
	/* "/" 以降を削除 */
	fullpath[n - 1] = 0;
	if (closedir(dp) < 0)
	{
		err_ret("can't close directory %s", fullpath);
	}
	return (ret);
}

/*
 * "pathname"から始めて階層構造を辿る。
 * 呼び出し側のfunc();を各ファイル毎に呼び出す。
 *
 * func()の戻り値を返す
 */
static int		myftw(char *pathname, Myfunc *func)
{
	/* (PATH_MAX + 1) bytesを割り付け */
	fullpath = path_alloc(&pathlen);

	/* （図2.16） */
	if (pathlen <= strlen(pathname))
	{
		pathlen = strlen(pathname) * 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL)
		{
			err_sys("realloc failed");
		}
	}
	strcpy(fullpath, pathname);
	return (dopath(func));
}

static int	myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch (type)
	{
		case FTW_F:
			switch (statptr->st_mode & S_IFMT)
			{
				case S_IFREG:	nreg++;		break;
				case S_IFBLK:	nblk++;		break;
				case S_IFCHR:	nchr++;		break;
				case S_IFIFO:	nfifo++;	break;
				case S_IFLNK:	nslink++;	break;
				case S_IFSOCK:	nsock++;	break;
				/* ディレクトリであれば、type = FTW_D のはず */
				case S_IFDIR:
					err_dump("for S_IFDIR for %s", pathname);
			}
			break;
		case FTW_D:
			ndir++;
			break ;
		case FTW_DNR:
			err_ret("can't read directory %s", pathname);
			break ;
		case FTW_NS:
			err_ret("stat error for %s", pathname);
			break ;
		default:
			err_dump("unknown type %d for pathname %s", type, pathname);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	ret;

	if (argc != 2)
	{
		err_quit("usage: ftw <starting-pathname>");
	}
	/* 全てを行う */
	ret = myftw(argv[1], myfunc);
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
	{
		/* ゼロ除算を回避；すべての個数に０を出力 */
		ntot = 1;
	}
	printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
	printf("directories    = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
	printf("block special  = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
	printf("char special   = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
	printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
	printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);
	exit(ret);
}
