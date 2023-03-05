/*
 * 『The Linux Programming Interface』p.97 ~
 * 5.5	Duplication File Descriptors
 *
 * #include <unistd.h>
 * int	dup(int oldfd);
 *
 * ERROR
 * return -1
 *
 * #include <unistd.h>
 * int	dup2(int oldfd, int mewfd);
 *
 * ERROR
 * return -1
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	fd1 = open("./sample1.txt", O_WRONLY | O_CREAT, 0644);
	int	fd2 = open("./sample2.txt", O_WRONLY | O_CREAT, 0644);
	int	fd2_cpy = 0;

	// fd1 == 3;
	// fd2 == 4;
	printf("fd1 [%d]\n", fd1);
	printf("fd2 [%d]\n", fd2);
	write(fd1, "Hello\n", 6);
	write(fd2, "world\n", 6);

	// fd2     == 4; --> sample2.txt
	// fd2_cpy == 0; --> sample2.txt
	dup2(fd2, fd2_cpy);
	printf("fd2     [%d]\n", fd2);
	printf("fd2_cpy [%d]\n", fd2_cpy);

	// close(fd2); 
	// fd2 == 4; --x--> sample2.txt
	// fd1 == 3; --> sample1.txt
	// fd2 == 4; --> sample1.txt
	dup2(fd1, fd2);
	printf("fd1 [%d]\n", fd1);
	printf("fd2 [%d]\n", fd2);

	write(fd1, "Hello\n", 6);
	write(fd2, "world\n", 6);

	// dup2(fd2_cpy, fd2);
	write(fd2_cpy, "world\n", 6);
}
