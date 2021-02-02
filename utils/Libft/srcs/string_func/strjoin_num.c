/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 04:02:54 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/18 02:43:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

/*
** this function puts a number after a string
** and doesn't take into account the minus.
*/

char			*strjoin_num(char *s, long long num)
{
	char		*res;
	long long	num_len;
	size_t		s_len;
	size_t		i;

	num_len = ft_numlen(num);
	s_len = ft_strlen(s);
	if (!(res = malloc(sizeof(char) * (s_len + num_len + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	while (num_len)
	{
		res[s_len + num_len - 1] = num % 10 + '0';
		num /= 10;
		num_len--;
		i++;
	}
	res[i] = '\0';
	return (res);
}
