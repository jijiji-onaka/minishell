/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:17:40 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:29:03 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_func.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	if (!b)
		return (NULL);
	ptr = (unsigned char*)b;
	while (len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		len--;
	}
	return (b);
}
