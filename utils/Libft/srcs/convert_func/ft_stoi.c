/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 01:25:32 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:31:40 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

static int	is_integer(char *s)
{
	if (*s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s)
		return (0);
	return (1);
}

int			ft_stoi(char *str, int *i)
{
	int res;
	int	neg;

	if (!is_integer(str))
	{
		ft_putstr_fd(str, 1);
		return (0);
	}
	res = 0;
	neg = 1;
	if (*str == '-' && str++)
		neg = -1;
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	*i = res * neg;
	return (1);
}
