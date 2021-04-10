/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 02:15:05 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:33:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/iswhat_func.h"

bool	is_float(char *s)
{
	bool	flag;

	flag = true;
	while (*s && (*s == '-' || *s == '+'))
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
	{
		flag = false;
		s++;
		while (ft_isdigit(*s))
			s++;
	}
	if (*s == '\0')
		return (!flag);
	return (!flag);
}
