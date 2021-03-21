/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:16:02 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/28 23:17:41 by tjinichi         ###   ########.fr       */
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
			res = (char *)s + i;
		i++;
	}
	return (res);
}
