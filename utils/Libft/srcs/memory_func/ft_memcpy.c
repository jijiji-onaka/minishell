/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:41:44 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:28:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_func.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_p;
	unsigned char	*src_p;

	if (!dst && !src)
		return (NULL);
	i = 0;
	dst_p = (unsigned char*)dst;
	src_p = (unsigned char*)src;
	while (i < n)
	{
		dst_p[i] = src_p[i];
		i++;
	}
	return (dst);
}
