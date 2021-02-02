/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:16:02 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/13 04:24:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*res;
	size_t	i;

	chr = (char)c;
	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == chr)
			res = (char *)s;
		i++;
	}
	if (chr == '\0')
		return ((char *)&(s[i]));
	return (res);
}
