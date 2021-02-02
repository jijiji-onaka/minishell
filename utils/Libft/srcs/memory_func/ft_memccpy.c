/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:28:34 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:28:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_func.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	if (!dst || !src)
		return (NULL);
	dst_p = (unsigned char*)dst;
	src_p = (unsigned char*)src;
	while (n > 0)
	{
		if ((*dst_p++ = *src_p++) == (unsigned char)c)
			return (dst_p);
		n--;
	}
	return (NULL);
}
