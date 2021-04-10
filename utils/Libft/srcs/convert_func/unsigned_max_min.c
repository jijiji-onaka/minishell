/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_max_min.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 02:36:02 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:36:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

size_t	unsigned_max(size_t x, size_t y)
{
	if (x >= y)
		return (x);
	return (y);
}

size_t	unsigned_min(size_t x, size_t y)
{
	if (x <= y)
		return (x);
	return (y);
}
