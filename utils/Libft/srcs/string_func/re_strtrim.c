/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:01:51 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:42:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*re_strtrim(char **freed, char *s1, char const *set)
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
		str = ft_strdup("");
	else
		str = ft_substr(s1, head, tail - head + 1);
	ptr_free((void **)freed);
	return (str);
}
