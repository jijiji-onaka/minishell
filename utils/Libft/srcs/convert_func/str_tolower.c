/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tolower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 05:58:27 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/31 17:11:53 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/convert_func.h"

void	str_tolower(char **s)
{
	char	*tmp;

	tmp = *s;
	while (*tmp)
	{
		*tmp = ft_tolower(*tmp);
		tmp++;
	}
}
