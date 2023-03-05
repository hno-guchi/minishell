#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int			j;
	char		**ep;
	extern char **environ;

	for (j = 0; j < argc; j++)
	{
		printf("argv[%d] = %s\n", j, argv[j]);
	}
	for (ep = environ; *ep != NULL; ep++)
	{
		printf("environ: %s\n", *ep);
	}
	exit (EXIT_SUCCESS);
}
