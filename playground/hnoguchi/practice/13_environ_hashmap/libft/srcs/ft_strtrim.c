/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:38:16 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/05/06 16:38:04 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	head_i;
	size_t	tail_i;
	char	*trim;

	if (s1 == NULL)
		return (ft_strdup(""));
	if (set == NULL)
		return (ft_strdup(s1));
	head_i = 0;
	while (s1[head_i] != '\0' && ft_strchr(set, s1[head_i]) != NULL)
		head_i += 1;
	tail_i = ft_strlen(s1);
	while (0 < tail_i && ft_strchr(set, s1[tail_i]) != NULL)
		tail_i -= 1;
	if (tail_i < head_i)
		return ((char *)ft_calloc(1, sizeof(char)));
	trim = ft_substr(s1, head_i, (tail_i - head_i) + 1);
	if (trim == NULL)
		return (NULL);
	return (trim);
}
