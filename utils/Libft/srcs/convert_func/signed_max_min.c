/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_max_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 05:26:38 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 05:30:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

long long	signed_max(long long x, long long y)
{
	if (x >= y)
		return (x);
	return (y);
}

long long	signed_min(long long x, long long y)
{
	if (x <= y)
		return (x);
	return (y);
}
