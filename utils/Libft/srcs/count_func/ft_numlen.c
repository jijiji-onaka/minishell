/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 01:57:21 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/17 22:12:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/count_func.h"

size_t		ft_numlen(long long n)
{
	size_t		cnt;

	cnt = 0;
	if (n <= 0)
	{
		n *= -1;
		cnt++;
	}
	while (n > 0)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}
