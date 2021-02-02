/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 02:15:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/22 02:15:39 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/iswhat_func.h"

bool		is_float(char *s)
{
	if (*s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s))
			s++;
	}
	if (*s)
		return (false);
	return (true);
}
