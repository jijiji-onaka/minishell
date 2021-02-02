/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 10:55:09 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

/*
** When head > tail
** ft_substr returns a valid empty string,
** but I'll return an empty character at strtrim.
*/

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	tail;
	char	*str;
	size_t	head;

	if (!s1 || !set)
		return (NULL);
	tail = ft_strlen(s1) - 1;
	head = 0;
	while (s1[head] && ft_strchr(set, s1[head]))
		head++;
	while (tail && ft_strchr(set, s1[tail]))
		tail--;
	if (head > tail)
		return (ft_strdup(""));
	else
		str = ft_substr(s1, head, tail - head + 1);
	return (str);
}
