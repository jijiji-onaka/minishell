/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 22:06:26 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/10 21:12:39 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/count_func.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	if (!str)
	{
		red_error();
		write(2, "The ft_strlen function has received a NULL argument.", 52);
		return (-1);
	}
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
