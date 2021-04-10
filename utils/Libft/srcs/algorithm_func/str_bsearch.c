/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_bsearch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:08:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:34:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algorithm_func.h"

int	str_bsearch(char *key, const char *base[], int array_size,
				int (*cmp_by)())
{
	int	left;
	int	right;
	int	mid;
	int	tmp;

	left = 0;
	right = array_size;
	if (left == right)
		return (0);
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid == array_size)
			return (mid);
		tmp = cmp_by(key, base[mid]);
		if (tmp == 0)
			return (mid);
		else if (tmp > 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (array_size);
}
