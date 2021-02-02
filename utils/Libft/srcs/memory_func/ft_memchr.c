/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 20:31:50 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:28:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_func.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;

	if (!s)
		return (NULL);
	str = (unsigned char*)s;
	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*str == chr)
		{
			return ((void*)str);
		}
		str++;
		n--;
	}
	return (NULL);
}
