/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 23:04:25 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_tmp;

	if (!s)
		return (NULL);
	s_tmp = (char *)s;
	while (*s_tmp)
	{
		if (*s_tmp == c)
			return (s_tmp);
		s_tmp++;
	}
	if (*s_tmp == '\0' && c == '\0')
		return (s_tmp);
	return (NULL);
}
