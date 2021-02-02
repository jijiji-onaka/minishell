/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 22:45:01 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:16 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (ft_strlen(src) + dstsize);
	i = 0;
	while (i < dstsize - dst_len - 1 && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (ft_strlen(src) + dst_len);
}
