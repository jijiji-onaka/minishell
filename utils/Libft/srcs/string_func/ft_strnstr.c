/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:39:14 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:26 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	haystack_len;
	size_t	needle_len;

	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char*)haystack);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (haystack_len < needle_len || needle_len > len)
		return (NULL);
	i = 0;
	while (*haystack && i <= len - needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char*)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
