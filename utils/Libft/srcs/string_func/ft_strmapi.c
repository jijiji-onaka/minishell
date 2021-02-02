/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:00:41 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/17 22:33:34 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*res;
	unsigned int		i;

	if (!f || !s)
		return (NULL);
	if (!(res = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
