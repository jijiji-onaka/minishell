/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 23:24:41 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:28:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_func.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(res = malloc(count * size)))
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
