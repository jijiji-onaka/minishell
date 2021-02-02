/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 23:24:47 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:09 by tjinichi         ###   ########.fr       */
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
	if (!(res = malloc(sizeof(char) * (len))))
		return (NULL);
	ft_memcpy(res, s1, len);
	return (res);
}
