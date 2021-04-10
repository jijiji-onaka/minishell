/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 01:45:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:41:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

char	*re_strjoin(char **freed, char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
	{
		ptr_free((void **)freed);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	ptr_free((void **)freed);
	return (res);
}
