/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:36:29 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:25:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char			*ft_str3join(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	if (!(res = malloc(len)))
		return (NULL);
	ft_strlcpy(res, s1, len);
	ft_strlcat(res, s2, len);
	ft_strlcat(res, s3, len);
	return (res);
}
