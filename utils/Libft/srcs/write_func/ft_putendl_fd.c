/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:23:36 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/11 16:31:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

bool	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return (false);
	if (ft_putstr_fd(s, fd) == false)
		return (false);
	if (write(fd, "\n", 1) < 0)
		return (false);
	return (true);
}
