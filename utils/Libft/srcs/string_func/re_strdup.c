/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 04:01:34 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/20 19:09:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*re_strdup(char **s1, char *s2)
{
	char	*res;
	size_t	len;

	if (*s1 == NULL)
		*s1 = ft_strdup("");
	len = ft_strlen(s2) + 1;
	if (!(res = malloc(sizeof(char) * (len))))
	{
		ptr_free((void**)s1);
		return (NULL);
	}
	ft_memcpy(res, s2, len);
	ptr_free((void**)s1);
	*s1 = res;
	return (res);
}
