/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:26:26 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/25 23:51:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

bool	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		if (!ft_putstr_fd("-2147483648", fd))
			return (false);
		return (true);
	}
	else if (n < 0)
	{
		if (!ft_putchar_fd('-', fd))
			return (false);
		if (!ft_putnbr_fd(-n, fd))
			return (false);
	}
	else if (n > 9)
	{
		if (!ft_putnbr_fd(n / 10, fd))
			return (false);
		if (!ft_putnbr_fd(n % 10, fd))
			return (false);
	}
	else if (!ft_putchar_fd(n + '0', fd))
		return (false);
	return (true);
}
