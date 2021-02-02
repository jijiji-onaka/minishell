/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtail_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:34:29 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

long long	strtail_number(char *s)
{
	long long	res;
	int			f;

	f = 0;
	res = 0;
	while (*s && *s != ']')
	{
		if (f == 1)
			res = res * 10 + (*s - '0');
		if (*s == '[')
			f = 1;
		s++;
	}
	if (*s != ']')
		return (1);
	return (res + 1);
}
