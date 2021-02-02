/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:02:04 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:14 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strjoinch(char const *s, char c)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		s = "";
	res = malloc(ft_strlen(s) + 1 + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (res);
}
