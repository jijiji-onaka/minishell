/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:51:45 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:31:31 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 63410682753376583680
*/

#include "../../includes/convert_func.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			f;

	i = 0;
	res = 0;
	f = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			f = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (res > (res * 10 + (str[i] - '0')) / 10)
			return (f == -1 ? (0) : (-1));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res * f);
}
