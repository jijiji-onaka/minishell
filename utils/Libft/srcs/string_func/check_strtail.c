/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strtail.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:37:53 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/12 01:39:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/string_func.h"

int			check_strtail(char *s, char *tail)
{
	char	*tmp;
	size_t	tail_len;

	tail_len = ft_strlen(tail);
	tmp = ft_substr(s, ft_strlen(s) - tail_len, tail_len);
	if (tmp == NULL)
		return (-1);
	if (ft_strncmp(tmp, tail, tail_len) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
