/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_regardless_of_case.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 04:49:40 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/20 04:49:56 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

int	strcmp_regardless_of_case(char *p1, char *p2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!p1 || !p2)
		return (INT_MIN);
	s1 = (unsigned char *)p1;
	s2 = (unsigned char *)p2;
	while (*s1 && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
