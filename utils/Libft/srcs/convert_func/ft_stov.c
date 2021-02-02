/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:46:08 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:32:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

int	ft_stov(char *s, t_p3 *p)
{
	char	**a;
	int		ret;
	int		count;

	if (!(a = ft_split(s, ',')))
		return (0);
	ret = 0;
	count = count_2d(a);
	if (count != 3)
	{
		ptr_2d_free((void***)&a, count);
		return (0);
	}
	if (!ft_stod(a[0], &(p->x)) ||
		!ft_stod(a[1], &(p->y)) ||
		!ft_stod(a[2], &(p->z)))
		ret = 1;
	ptr_2d_free((void***)&a, count);
	if (ret == 1)
		return (0);
	return (1);
}
