/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:32:53 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/17 22:10:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

/*
** Returns allocate.
*/

char			*ft_itoa(int n)
{
	char	*res;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(res = malloc(sizeof(char) * (ft_numlen(n) + 1))))
		return (NULL);
	i = ft_numlen(n) - 1;
	res[i + 1] = '\0';
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	while (n != 0)
	{
		res[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (res);
}
