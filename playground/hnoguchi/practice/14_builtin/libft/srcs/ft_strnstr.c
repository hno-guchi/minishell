/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:10:43 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:14:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_skip_asciitab(const char *key, size_t *table, size_t key_siz);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		hay_c;
	size_t		nee_siz;
	size_t		skip_table[256];

	if (ft_strncmp(needle, "", 1) == 0)
		return ((char *)haystack);
	if (len == 0 || ft_strncmp(haystack, "", 1) == 0)
		return (NULL);
	hay_c = 0;
	nee_siz = ft_strlen(needle);
	i = nee_siz - 1;
	make_skip_asciitab(needle, skip_table, nee_siz);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[nee_siz - 1])
			if (ft_strncmp(&haystack[i - nee_siz + 1], needle, nee_siz) == 0)
				return ((char *)&haystack[i - nee_siz + 1]);
		hay_c = haystack[i];
		i += skip_table[hay_c];
	}
	return (NULL);
}

static void	make_skip_asciitab(const char *key, size_t *table, size_t key_siz)
{
	size_t	i;
	size_t	key_c;

	i = 0;
	key_c = 0;
	while (i < 256)
	{
		table[i] = key_siz;
		i += 1;
	}
	i = 0;
	while (i < (key_siz - 1))
	{
		key_c = key[i];
		table[key_c] = key_siz - 1 - i;
		i += 1;
	}
	return ;
}
