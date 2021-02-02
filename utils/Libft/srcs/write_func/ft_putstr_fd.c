/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:20:01 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/08 00:45:22 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

bool	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (false);
	if (write(fd, s, ft_strlen(s)) < 0)
		return (false);
	return (true);
}
