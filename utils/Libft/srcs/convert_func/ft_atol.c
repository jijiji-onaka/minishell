/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 02:17:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:02:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

long long	ft_atol(const char *str, bool *overflow, bool *digit_flag)
{
	int			i;
	long long	res;
	int			f;

	i = 0;
	res = 0;
	f = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		f = 44 - str[i++];
	if (str[i] == '-' || str[i] == '+' || str[i] == '\0')
		return ((*digit_flag = true));
	while (ft_isdigit(str[i]))
	{
		if (res != (res * 10 + str[i] - '0') / 10 && res != 922337203685477580)
			return (!(*overflow = true));
		res = res * 10 + (str[i++] - '0');
	}
	if (str[i] != '\0' && str[i] != ' ')
		return ((*digit_flag = true));
	if (((res * f < 0 && f == 1) || (res * f > 0 && f == -1)))
		*overflow = true;
	return (res * f);
}
