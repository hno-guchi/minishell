/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtol_base_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:25:16 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/03/24 20:11:19 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_strtol(long long *sign, const char **rest, const char *nptr)
{
	while (ft_isspace(*nptr))
	{
		nptr += 1;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
		{
			*sign = -1;
		}
		nptr += 1;
	}
	if (!ft_isdigit(*nptr))
	{
		errno = 22;
		return (-1);
	}
	*rest = nptr;
	return (0);
}

static long	destructor_strtol(long long sign, long long last_num,
				const char *nptr, char **endptr)
{
	int	diff;

	diff = last_num - (LONG_MAX - (*nptr - '0')) / 10;
	if (sign == -1)
	{
		if (!(1 == diff && 8 == (*nptr - '0')))
			errno = 34;
		else if (ft_isdigit(*(nptr + 1)))
			errno = 34;
		while (ft_isdigit(*nptr))
		{
			nptr += 1;
		}
		*endptr = (char *)nptr;
		return (LONG_MIN);
	}
	errno = 34;
	while (ft_isdigit(*nptr))
	{
		nptr += 1;
	}
	*endptr = (char *)nptr;
	return (LONG_MAX);
}

long	strtol_base_10(const char *nptr, char **endptr)
{
	long long	ll_number;
	long long	sign;

	ll_number = 0;
	sign = 1;
	*endptr = (char *)nptr;
	errno = 0;
	if (prepare_strtol(&sign, &nptr, nptr) != 0)
	{
		return (0);
	}
	while (ft_isdigit(*nptr))
	{
		if (ll_number <= (LONG_MAX - (*nptr - '0')) / 10)
		{
			ll_number = (ll_number * 10) + (*nptr - '0');
		}
		else
		{
			return (destructor_strtol(sign, ll_number, nptr, endptr));
		}
		nptr += 1;
	}
	*endptr = (char *)nptr;
	return ((long)(ll_number * sign));
}

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*endptr;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Please argment...\n");
		exit (EXIT_FAILURE);
	}
	endptr = NULL;
	printf("[REFERENCE]\n");
	printf("-----------------------------------------\n");
	printf("|  LONG_MIN   : [%21ld] |\n", LONG_MIN);
	printf("|  LONG_MAX   : [%21ld] |\n", LONG_MAX);
	printf("| LLONG_MIN   : [%21lld] |\n", LLONG_MIN);
	printf("| LLONG_MAX   : [%21lld] |\n", LLONG_MAX);
	printf("-----------------------------------------\n\n");
	printf("TEST   : [%s]\n", argv[1]);
	errno = 0;
	printf("strtol : (%d); endptr : [%c](%p); errno : (%d)\n",
		(int)strtol(argv[1], &endptr, 10), *endptr, endptr, errno);
	if (errno)
		perror("strtol ");
	endptr = NULL;
	errno = 0;
	printf("ft     : (%d); endptr : [%c](%p); errno : (%d)\n",
		(int)strtol_base_10(argv[1], &endptr), *endptr, endptr, errno);
	if (errno)
		perror("ft     ");
}
*/
