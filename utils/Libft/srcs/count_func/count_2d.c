/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:33:56 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/17 22:30:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/count_func.h"

size_t	count_2d(char **array_2d)
{
	size_t i;

	if (array_2d == NULL)
	{
		red_error();
		ft_putendl_fd("The count_2d function has received a NULL argument.", 2);
		return (-1);
	}
	i = 0;
	while (array_2d[i])
		i++;
	return (i);
}
