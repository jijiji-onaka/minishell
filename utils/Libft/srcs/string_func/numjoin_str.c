/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numjoin_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 01:46:14 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/22 01:59:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char			*numjoin_str(char *s, long long num)
{
	char		*res;
	long long	num_len;
	size_t		s_len;
	size_t		i;
	size_t		j;

	num_len = ft_numlen(num);
	s_len = ft_strlen(s);
	if (!(res = malloc(sizeof(char) * (s_len + num_len + 1))))
		return (NULL);
	i = 0;
	while (num_len)
	{
		res[num_len - 1] = num % 10 + '0';
		num_len--;
		num /= 10;
		i++;
	}
	j = -1;
	while (s[++j])
		res[i++] = s[j];
	res[i + num_len] = '\0';
	return (res);
}
