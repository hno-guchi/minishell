/*
 * 『The Linux Programming Interface』p.71
 *
 * This program is a simple version of the cp(1) command.
 *
 * ex)
 * ~$ ./copy old_file new_file
 */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

/* Allow "cc -D" to override definition */
#ifndef BUF_SIZE
# define BUF_SIZE 1024
#endif

int	main(int argc, char *argv[])
{
	int		input_fd;
	int		output_fd;
	int		open_flags;
	mode_t	file_parameters;
	ssize_t	num_read;
	char	buf[BUF_SIZE];

	if (argc != 3 || (strcmp(argv[1], "--help") == 0))
	{
		usageErr("%s old_file new_file \n", argv[0]);
	}

	/* Open input and output file */
	if ((input_fd = open(argv[1], O_RDONLY)) == -1)
	{
		errExit("opening file %s", argv[1]);
	}
	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_parameters = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */
	if ((output_fd = open(argv[2], open_flags, file_parameters)) == -1)
	{
		errExit("opening file %s", argv[2]);
	}
	/* Transfer data until we encounter end of input or an error */
	while (0 < (num_read = read(input_fd, buf, BUF_SIZE)))
	{
		if (write(output_fd, buf, num_read) != num_read)
		{
			fatal("couldn't write whole buffer");
		}
	}
	if (num_read == -1)
	{
		errExit("read");
	}
	if (close(input_fd) == -1)
	{
		errExit("close input");
	}
	if (close(output_fd) == -1)
	{
		errExit("close output");
	}
	exit (EXIT_SUCCESS);
}
