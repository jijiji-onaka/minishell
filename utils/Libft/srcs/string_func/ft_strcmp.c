/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:46:55 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:07 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

int	ft_strcmp(char *p1, char *p2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!p1 || !p2)
		return (INT_MIN);
	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
