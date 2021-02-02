/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_strjoinch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 04:21:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/11 16:01:00 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*re_strjoinch(char **s, char c)
{
	char	*res;
	size_t	i;

	if (s == NULL)
	{
		write(1, "The ft_strlen function has received a NULL argument.", 52);
		return (NULL);
	}
	if (*s == NULL)
		*s = ft_strdup("");
	if (!(res = malloc(ft_strlen(*s) + 1 + 1)))
	{
		ptr_free((void**)s);
		return (NULL);
	}
	i = 0;
	while ((*s)[i])
	{
		res[i] = (*s)[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	ptr_free((void**)s);
	return (res);
}
