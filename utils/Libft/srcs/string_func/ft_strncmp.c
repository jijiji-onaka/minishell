/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:52:56 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:26:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	if (!s1 || !s2)
		return (INT_MIN);
	i = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (u_s1[i] == '\0' || u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	return (0);
}
