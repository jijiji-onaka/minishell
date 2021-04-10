/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 23:24:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:37:57 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;

	if (s1 == NULL)
		return (ft_strdup(""));
	len = ft_strlen(s1) + 1;
	res = malloc(sizeof(char) * (len));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, len);
	return (res);
}
